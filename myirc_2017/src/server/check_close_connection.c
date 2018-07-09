/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** check_close_connection
*/

#include <unistd.h>
#include "server.h"

void close_all_socket(server_t server, int nfds)
{
	for (int i = 0; i < nfds; i++) {
		if (server->fds[i].fd >= 0)
			close(server->fds[i].fd);
	}
}

void close_connection(server_t server, int *nfds)
{
	if (!server->compress_fd)
		return;
	server->compress_fd = false;
	for (int i = 0; i < *nfds; i++) {
		if (server->fds[i].fd != -1)
			continue;
		for (int j = i; j < *nfds; j++)
			server->fds[j].fd = server->fds[j+1].fd;
		i--;
		*nfds -= 1;
	}
}

void check_close_connection(server_t server, bool close_conn, int current_index)
{
	if (close_conn) {
		shutdown(server->fds[current_index].fd, SHUT_RDWR);
		close(server->fds[current_index].fd);
		server->fds[current_index].fd = -1;
		server->compress_fd = true;
	}
}
