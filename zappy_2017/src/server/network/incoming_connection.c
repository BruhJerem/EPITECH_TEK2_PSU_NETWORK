/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Incoming connection
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

bool incoming_connection(server_t server)
{
	socket_t new_socket = accept_socket(server->socket);
	player_client_t player;

	if (!new_socket)
		return false;
	if (server->nfds >= 1020) {
		printf(S_CONNECTION_REFUSED);
		dprintf(new_socket->fd, C_CONNECTION_REFUSED);
		disconnect_socket(new_socket);
		return false;
	}
	printf(S_CONNECTION_WELCOME, new_socket->fd);
	server->poll_fds[server->nfds].fd = new_socket->fd;
	server->poll_fds[server->nfds].events = POLLIN;
	player = create_player_client(server, new_socket, server->nfds);
	add_player(&server->players, player);
	server->nfds++;
	dprintf(new_socket->fd, C_CONNECTION_WELCOME);
	return true;
}
