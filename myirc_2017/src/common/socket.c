/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Socket functions
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "server.h"

socket_t create_socket(char *address, unsigned short port)
{
	int fd;
	struct protoent	*pe = getprotobyname("TCP");
	int on = 1;
	socket_t new_socket = malloc(sizeof(struct s_socket));

	if (!new_socket || !pe)
		return NULL;
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return NULL;
	setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, (char *) &on, sizeof(on));
	new_socket->fd = fd;
	new_socket->port = port;
	new_socket->ip = address;
	return new_socket;
}

bool destruct_socket(socket_t socket)
{
	if (socket == NULL)
		return false;
	if (shutdown(socket->fd, SHUT_RDWR) == -1) {
		if (close(socket->fd) == -1) {
			free(socket);
			return false;
		}
		free(socket);
		return false;
	}
	if (close(socket->fd) == -1) {
		free(socket);
		return false;
	}
	free(socket);
	return true;
}
