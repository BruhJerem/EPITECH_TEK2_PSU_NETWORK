/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** start_server
*/

#include <stdbool.h>
#include <stdio.h>
#include <netdb.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <error.h>
#include "server.h"

/**
* Listen socket connection and limit the queue of connection
* @param serv
* @param max_client
* @return
*/

bool listen_server(server_t *serv, int max_client)
{
	if (listen(serv->fd, max_client) == -1) {
		if (close(serv->fd) == -1)
			return false;
		return false;
	}
	return true;
}

/**
* Accept a new connection on a socket
* @param serv
* @return
*/

server_t *accept_server(server_t *serv)
{
	int client_fd;
	socklen_t s_in_size = sizeof(serv->s_in_client);

	client_fd = accept(serv->fd, (struct sockaddr *)
		&serv->s_in_client, &s_in_size);
	if (client_fd == -1) {
		return NULL;
	}
	serv->client_fd = client_fd;
	return serv;
}

/**
* Start begin of the server
* @param serv
* @return
*/

bool start_server(server_t *serv)
{
	struct sockaddr_in s_in;
	socklen_t s_in_len = sizeof(s_in);

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(serv->port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(serv->fd, (const struct sockaddr *) &s_in, s_in_len) == -1) {
		printf("Port already in use.\n");
		if (close(serv->fd) == -1)
			return false;
		return false;
	}
	return listen_server(serv, 42);
}