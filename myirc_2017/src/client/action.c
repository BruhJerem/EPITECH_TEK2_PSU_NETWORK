/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Action functions
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

void send_message(client_t client, char *line)
{
	if (client->socket != NULL)
		send(client->socket->fd, line, strlen(line), 0);
	else
		printf("To send message, please connect to a server\n");
}

bool send_command_to_server(int server_fd, char **command)
{
	ssize_t return_code;
	char *buffer = NULL;

	buffer = transform_command(command);
	if (buffer == NULL)
		return false;
	buffer = realloc(buffer, strlen(buffer) + 2);
	strcat(buffer, "\r\n");
	return_code = send(server_fd, buffer, strlen(buffer), 0);
	if (return_code == -1)
		return false;
	return true;
}

static bool read_client(client_t client)
{
	ssize_t cread = 0;
	char buffer[BUFF_SIZE];

	memset(buffer, 0, BUFF_SIZE);
	cread = read(0, buffer, BUFF_SIZE);
	if (cread == -1) {
		printf("read error\n");
		return false;
	} else if (cread == 0)
		return false;
	route_command(client, buffer);
	return true;
}

static bool read_server(client_t client)
{
	char buffer[BUFF_SIZE];

	memset(buffer, 0, BUFF_SIZE);
	if (recv(client->socket->fd, buffer, BUFF_SIZE, 0) < 0)
		return false;
	printf("%s", buffer);
	return true;
}

bool handling_event(client_t client)
{
	if (client->fds[0].revents & POLLIN) {
		if (!read_client(client))
			return false;
	}
	if (client->socket != NULL && client->fds[1].revents & POLLIN) {
		if (!read_server(client))
			return false;
	}
	return true;
}
