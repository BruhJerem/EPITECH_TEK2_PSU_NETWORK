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
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "server.h"

/**
* Bind the socket
* @param argv
* @return
*/

bool set_bind(socket_t socket)
{
	struct sockaddr_in addr;
	int rc;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy(&addr.sin_addr, &in6addr_any, sizeof(in6addr_any));
	addr.sin_port = htons(socket->port);
	rc = bind(socket->fd, (struct sockaddr *) &addr, sizeof(addr));
	if (rc < 0) {
		perror("bind() failed");
		close(socket->fd);
		exit(84);
	}
	return true;
}

bool set_listen(socket_t socket)
{
	int rc = listen(socket->fd, 32);

	if (rc < 0) {
		perror("listen() failed");
		close(socket->fd);
		exit(84);
	}
	return true;
}

int set_accept(socket_t socket)
{
	int client_fd;
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);

	client_fd = accept(socket->fd, (struct sockaddr *)
		&s_in_client, &s_in_size);
	if (client_fd == -1)
		return -1;
	return client_fd;
}
