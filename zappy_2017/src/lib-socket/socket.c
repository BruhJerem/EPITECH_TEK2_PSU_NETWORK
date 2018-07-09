/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Socket creation/destruction
*/

#include <stdbool.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib-socket.h"

socket_t create_socket(char *address, ushort_t port, bool re_use_addr)
{
	struct protoent	*pe = getprotobyname("TCP");
	socket_t new_socket = malloc(sizeof(struct s_socket));
	int enable = 1;
	int fd;

	if (!new_socket || !pe)
		return NULL;
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return NULL;
	if (re_use_addr == true)
		setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, &enable, sizeof(int));
	new_socket->fd = fd;
	new_socket->port = port;
	new_socket->address = address;
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

bool disconnect_socket(socket_t socket)
{
	return destruct_socket(socket);
}
