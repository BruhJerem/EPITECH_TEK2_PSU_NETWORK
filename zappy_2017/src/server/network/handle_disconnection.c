/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Handle disconnection
*/

#include <stdio.h>
#include "server.h"

static void disconnect_player(server_t server, size_t index)
{
	player_client_t current_player;
	team_list_t team_list = server->teams;
	team_t team = NULL;

	printf("User disconnected - %d\n", server->poll_fds[index].fd);
	current_player = get_player_by_fd(
		server->players, server->poll_fds[index].fd);
	if (!current_player) {
		printf("WTF\n");
		return;
	}
	team = get_team_by_name(team_list,
				current_player->team_name);
	if (team)
		team->nbr_player--;
	server->nbr_player--;
	delete_player_by_fd(&server->players, server->poll_fds[index].fd);
	destruct_socket(current_player->socket);
}

static void disconnect_ui(server_t server, size_t index)
{
	printf("Graphic disconnected - %d\n", server->poll_fds[index].fd);
	destruct_socket(server->ui->socket);
	server->ui = NULL;
}

bool handle_disconnection(server_t server, size_t index)
{
	player_client_t player = NULL;
	int player_fd;

	player_fd = server->poll_fds[index].fd;
	if (server->ui && player_fd == server->ui->socket->fd)
		disconnect_ui(server, index);
	else {
		player = get_player_by_fd(server->players, player_fd);
		player_disconnect_event(server, player);
		disconnect_player(server, index);
	}
	server->poll_fds[index].fd = -1;
	server->compress_fd = true;
	return false;
}
