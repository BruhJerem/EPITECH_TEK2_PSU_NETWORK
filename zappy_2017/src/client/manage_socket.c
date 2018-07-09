/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Socket Management
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include "client.h"

void destruct_client_socket(t_client *client)
{
	if (client) {
		shutdown(client->fd, SHUT_RDWR);
		close(client->fd);
		free(client->name);
	}
}

void copy_client_struct(t_client *client, t_client *new_client)
{
	new_client->machine = strdup(client->machine);
	new_client->port = client->port;
	new_client->name = strdup(client->name);
	new_client->fd = 0;
	new_client->hash = 0;
}

bool create_client_socket(t_client *client)
{
	struct protoent *pe = getprotobyname("TCP");
	if ((client->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(client->port);
	sin.sin_addr.s_addr = inet_addr(client->machine);
	if (connect(client->fd, (struct sockaddr *)&sin, sizeof(sin)))
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	return true;
}
