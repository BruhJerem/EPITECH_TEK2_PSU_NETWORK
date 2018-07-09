/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** User functions
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "client.h"

bool command_nick(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_msg(client_t client, char **command)
{
	if (!send_command_to_server(client->socket->fd, command))
		return false;
	return true;
}

bool command_accept_file(client_t client, char **command)
{
	(void) client;
	(void) command;
	return true;
}
