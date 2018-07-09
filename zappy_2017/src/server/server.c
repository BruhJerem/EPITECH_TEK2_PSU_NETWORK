/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server base functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>
#include "server.h"
#include "arg_parser.h"

server_t init_server(arg_t args)
{
	server_t new_server = malloc(sizeof(struct s_server));

	if (!new_server)
		return NULL;
	new_server->socket = create_socket("127.0.0.1", args->port, true);
	if (!new_server->socket)
		return NULL;
	if (!bind_socket(new_server->socket))
		return NULL;
	if (!listen_socket(new_server->socket))
		return NULL;
	memset(new_server->poll_fds, 0, sizeof(new_server->poll_fds));
	new_server->poll_fds[0].fd = new_server->socket->fd;
	new_server->poll_fds[0].events = POLLIN;
	new_server->nfds = 1;
	new_server->nbr_player_max_team = args->client_nb;
	new_server->action_freq = args->freq;
	new_server->nbr_player = 0;
	new_server->compress_fd = false;
	new_server->ui = NULL;
	new_server->players = NULL;
	new_server->teams = init_team_list(args->team_name);
	new_server->map = init_map(args->height, args->width);
	if (!new_server->map)
		return NULL;
	if (!generate_map(new_server->map))
		return NULL;
	// @todo [URGENT] Lancer fonction qui free toute la structure de ludo
	return new_server;
}

static bool handling_events(server_t server, size_t index)
{
	if (server->poll_fds[index].revents == 0)
		return true;
	if (server->poll_fds[index].fd == server->socket->fd)
		return incoming_connection(server);
	else
		return handle_readable(server, index);
}

void close_connection(server_t server)
{
	if (!server->compress_fd)
		return;
	server->compress_fd = false;
	for (int i = 0; i < (int) server->nfds; i++) {
		if (server->poll_fds[i].fd != -1)
			continue;
		for (int j = i; j < (int) server->nfds; j++)
			server->poll_fds[j].fd = server->poll_fds[j + 1].fd;
		i--;
		server->nfds -= 1;
	}
}

bool server_loop(server_t server)
{
	int rc;
	size_t size;

	printf("Port : %d\n", server->socket->port);
	while (true) {
		printf("Waiting on poll()...\n");
		rc = poll(server->poll_fds, server->nfds, -1);
		if (rc < 0) {
			perror("poll() failed");
			break;
		} else if (rc == 0)
			break;
		size = (size_t) server->nfds;
		for (size_t i = 0; i < size; ++i) {
			rc = handling_events(server, i);
			if (rc == false)
				break;
		}
		close_connection(server);
	}
	disconnect_socket(server->socket);
	return true;
}
