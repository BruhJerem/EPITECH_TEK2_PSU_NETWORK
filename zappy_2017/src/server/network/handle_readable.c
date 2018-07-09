/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_readable
*/

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <lib-tools.h>
#include "server.h"

static bool concat_str_ui(server_t server, char c[1])
{
	if (c[0] == '\n' && server->ui->buffer[0] == '\0')
		return false;
	if (strlen(server->ui->buffer) >= READ_SIZE)
		memset(server->ui->buffer, 0, READ_SIZE);
	if (c[0] != '\n') {
		strcat(server->ui->buffer, c);
		return false;
	}
	return true;
}

static bool concat_str(server_t server, char c[1], size_t index, bool is_ui)
{
	player_client_t current_player = NULL;

	if (!is_ui) {
		current_player = get_player_by_fd(
			server->players, server->poll_fds[index].fd);
		if (!current_player || (c[0] == '\n' &&
			current_player->buffer[0] == '\0'))
			return false;
		if (strlen(current_player->buffer) + 1 >= READ_SIZE)
			memset(current_player->buffer, 0, READ_SIZE);
		if (c[0] != '\n') {
			strcat(current_player->buffer, c);
			return false;
		}
	}
	if (is_ui) {
		return concat_str_ui(server, c);
	}
	return true;
}

static bool set_team_name(server_t server, player_client_t cur_player,
				size_t idx)
{
	team_list_t teams = server->teams;
	team_t team = NULL;

	if (!strcmp(cur_player->buffer, UI_CONNECTION_MSG))
		return add_ui_to_server(server, cur_player, idx);
	team = get_team_by_name(teams, cur_player->buffer);
	if (!team)
		return false;
	cur_player->team_name = strdup(cur_player->buffer);
	if (team->nbr_player + 1 > server->nbr_player_max_team)
		return false;
	team->nbr_player++;
	player_connect_event(server, cur_player);
	dprintf(server->poll_fds[idx].fd, "%d\n",
		server->nbr_player_max_team - team->nbr_player);
	dprintf(server->poll_fds[idx].fd, "%lu %lu\n",
		server->map->width, server->map->height);
	return true;
}

static void redirect(server_t server, char c[2], size_t index, bool is_ui)
{
	player_client_t current_player = NULL;
	bool success = true;

	if (!is_ui) {
		current_player = get_player_by_fd(
			server->players, server->poll_fds[index].fd);
	}
	if (concat_str(server, c, index, is_ui)) {
		if (!is_ui && current_player->state == AWAITING_TEAM_NAME) {
			success = set_team_name(server, current_player, index);
			memset(current_player->buffer, 0, READ_SIZE);
		} else if (!is_ui) {
			command_router(server, current_player->buffer, index);
			memset(current_player->buffer, 0, READ_SIZE);
		} else {
			command_router(server, server->ui->buffer, index);
			memset(server->ui->buffer, 0, READ_SIZE);
		}
	}
	if (!success)
		dprintf(server->poll_fds[index].fd, "ko\n");
}

bool handle_readable(server_t server, size_t index)
{
	char c[2];
	int rc;
	bool is_ui = false;

	memset(c, 0, 2);
	rc = (int) read(server->poll_fds[index].fd, &c, 1);
	if (rc < 0) {
		perror("read() failed");
		return false;
	}
	if (rc == 0)
		return handle_disconnection(server, index);
	if (server->ui && server->poll_fds[index].fd == server->ui->socket->fd)
		is_ui = true;
	redirect(server, c, index, is_ui);
	return true;
}
