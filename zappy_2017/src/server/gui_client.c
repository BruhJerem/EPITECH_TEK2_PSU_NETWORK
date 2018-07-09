/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** UI Client
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

ui_client_t create_ui_client(server_t server, socket_t socket, nfds_t poll_idx)
{
	ui_client_t ui_client;

	if (!socket || server->ui)
		return NULL;
	ui_client = malloc(sizeof(struct s_ui_client));
	if (!ui_client)
		return NULL;
	memset(ui_client->buffer, 0, READ_SIZE);
	ui_client->socket = socket;
	ui_client->poll_idx = poll_idx;
	server->nbr_player--;
	return ui_client;
}

static void send_ui_init(server_t server, int fd)
{
	dprintf(fd, C_MSZ, server->map->width, server->map->height);
	dprintf(fd, C_SGT, server->action_freq);
	send_tiles_inventory(server, fd);
	send_teams(server, fd);
}

bool add_ui_to_server(server_t server, player_client_t cur_player, size_t idx)
{
	ui_client_t ui_client;

	ui_client = create_ui_client(server, cur_player->socket,
					cur_player->poll_idx);
	if (!ui_client) {
		printf("Error: Graphical Interface already connected.\n");
		handle_disconnection(server, idx);
		return false;
	}
	printf("I'm the graphical Interface\n");
	delete_player_by_fd(&server->players, server->poll_fds[idx].fd);
	send_ui_init(server, server->poll_fds[idx].fd);
	server->ui = ui_client;
	return true;
}
