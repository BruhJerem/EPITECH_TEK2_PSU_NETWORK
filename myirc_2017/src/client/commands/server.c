/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Server commands
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "client.h"

bool command_server(client_t client, char **command)
{
	char **tab = NULL;
	unsigned short port;

	if (tab_len(command) != 2)
		return false;
	tab = str_to_wordtab(command[1], ':');
	if (tab == NULL || tab_len(tab) == 0)
		return false;
	port = (unsigned short) atoi(tab[1]);
	client->socket = create_socket(tab[0], port);
	if (client->socket == NULL || !connect_socket(client->socket)) {
		printf(CS_FAILED);
		client->socket = NULL;
		return false;
	}
	client->fds[1].fd = client->socket->fd;
	client->fds[1].events = POLLIN;
	client->nfds++;
	printf(CS_CONNECTED, client->socket->ip, client->socket->port);
	return true;
}

bool command_list(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_users(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_disconnect(client_t client, char **command)
{
	(void) command;

	if (client->socket == NULL)
		return false;
	if (!destruct_socket(client->socket)) {
		printf("Error in the disconnect request\n");
		return false;
	}
	client->socket = NULL;
	printf("Disconnected from the server\n");
	return true;
}
