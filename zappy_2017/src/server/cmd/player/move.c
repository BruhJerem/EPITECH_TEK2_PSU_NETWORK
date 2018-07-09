/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Move player cmd
*/

#include <stdio.h>
#include "server.h"

bool forward(server_t server, char **cmd, int index)
{
	player_client_list_t list = server->players;
	player_client_t player_client = get_player_by_fd(
		list, server->poll_fds[index].fd);

	(void) cmd;
	forward_player(server->map, player_client);
	dprintf(server->poll_fds[index].fd, "ok\n");
	return true;
}

bool left(server_t server, char **cmd, int index)
{
	player_client_list_t list = server->players;
	player_client_t player_client = get_player_by_fd(
		list, server->poll_fds[index].fd);

	(void) cmd;
	left_player(player_client);
	dprintf(server->poll_fds[index].fd, "ok\n");
	return true;
}

bool right(server_t server, char **cmd, int index)
{
	player_client_list_t list = server->players;
	player_client_t player_client = get_player_by_fd(
		list, server->poll_fds[index].fd);

	(void) cmd;
	right_player(player_client);
	dprintf(server->poll_fds[index].fd, "ok\n");
	return true;
}
