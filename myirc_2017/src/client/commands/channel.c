/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Channel functions
*/

#include "client.h"

bool command_join(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_part(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_names(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}
