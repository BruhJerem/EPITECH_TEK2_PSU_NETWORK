/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** start_process
*/

#include <stdbool.h>
#include <server.h>
#include <stdio.h>
#include <sys/poll.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int incoming_connection(server_t server, int *nfds)
{
	int new_sd;
	client_list_t tmp = server->client_list;
	channel_list_t channel_list = server->channel_list;
	client_t new_client;

	new_sd = set_accept(server->socket);
	if (new_sd < 0) {
		if (errno != EWOULDBLOCK) {
			perror("  accept() failed");
			server->end_server = true;
		}
	}
	printf("  New incoming connection - %d\n", new_sd);
	server->fds[*nfds].fd = new_sd;
	server->fds[*nfds].events = POLLIN;
	*nfds += 1;
	new_client = create_client(new_sd, "*");
	client_add_elem_at_back(tmp, new_client);
	tmp->client->channel = channel_get_elem_by_name(channel_list, "*");
	dprintf(new_sd, RPL_AUTHENTICATION, server->socket->ip, "*");
	return 0;
}

/**
* @return 1 is Continue, 84 break
*/

static int handling_process(server_t server, int current_index, int *nfds)
{
	if (server->fds[current_index].revents == 0)
		return 1;
	if (server->fds[current_index].revents != POLLIN) {
		printf("  Error ! revents = %d\n",
			server->fds[current_index].revents);
		server->end_server = true;
		return 84;
	}
	if (server->fds[current_index].fd == server->socket->fd)
		return incoming_connection(server, nfds);
	else
		return handle_readable(server, current_index);
}

void start_process(server_t server)
{
	int nfds = 1;
	int rc;

	while (!server->end_server) {
		printf("Waiting on poll()...\n");
		rc = poll(server->fds, (nfds_t) nfds, -1);
		if (rc < 0) {
			perror("  poll() failed");
			break;
		} else if (rc == 0)
			break;
		server->size_client = nfds;
		for (int i = 0; i < server->size_client; ++i) {
			rc = handling_process(server, i, &nfds);
			if (rc == 1)
				continue;
			if (rc == 84)
				break;
		}
		close_connection(server, &nfds);
	}
	close_all_socket(server, nfds);
}
