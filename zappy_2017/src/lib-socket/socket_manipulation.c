/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Socket manipulation
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "lib-socket.h"

bool connect_socket(socket_t socket)
{
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons((uint16_t) socket->port);
	sin.sin_addr.s_addr = inet_addr(socket->address);
	if (connect(socket->fd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		perror("connect() failed");
		if (close(socket->fd) == -1)
			return false;
		return false;
	}
	return true;
}

bool bind_socket(socket_t socket)
{
	struct sockaddr_in sin;
	socklen_t sin_size = sizeof(sin);
	int rc;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((uint16_t) socket->port);
	rc = bind(socket->fd, (struct sockaddr *) &sin, sin_size);
	if (rc < 0) {
		perror("bind() failed");
		close(socket->fd);
		return false;
	}
	return true;
}

bool listen_socket(socket_t socket)
{
	int rc = listen(socket->fd, 32);

	if (rc < 0) {
		perror("listen() failed");
		close(socket->fd);
		return false;
	}
	return true;
}

socket_t accept_socket(socket_t socket)
{
	int client_fd;
	struct sockaddr_in sin;
	socklen_t sin_size = sizeof(sin);
	socket_t client_socket = malloc(sizeof(struct s_socket));

	if (!client_socket)
		return NULL;
	client_fd = accept(socket->fd, (struct sockaddr *) &sin, &sin_size);
	if (client_fd == -1)
		return NULL;
	client_socket->fd = client_fd;
	client_socket->port = (short) ntohs(sin.sin_port);
	client_socket->address = inet_ntoa(sin.sin_addr);
	return client_socket;
}
