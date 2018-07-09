/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Misc functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"

bool command_help(client_t client, char **command)
{
	(void) client;
	(void) command;
	printf("%s", "[IRC CLIENT] Commands :\n");
	printf("%s", "\t/help\t\tprint help.\n");
	printf("%s", "\t/server\t\tconnects to a server.\n");
	printf("%s", "\t/nick\t\tdefines the user’s nickname in the server.\n");
	printf("%s", "\t/list\t\tlists the server’s available channels.\n");
	printf("%s", "\t/join\t\tjoins a server’s channel.\n");
	printf("%s", "\t/part\t\tleaves a channel.\n");
	printf("%s", "\t/users\t\tlists the nicknames of the users that are "
		"connected to the server.\n");
	printf("%s", "\t/names\t\tlists the nicknames of the users connected "
		"to the channel.\n");
	printf("%s", "\t/msg\t\tsends a message to a specific user.\n");
	printf("%s", "\t/part\t\taccepts the reception of a file coming from "
		"one of the channel’s users.\n");
	printf("%s", "\t/accept_file\tleaves a channel.\n");
	printf("%s", "\t/disconnect\tdisconnect the server connected to.\n");
	printf("%s", "\t/quit\t\tquit client and the server connected to.\n");
	return true;
}

bool command_quit(client_t client, char **command)
{
	(void) command;
	if (client->socket != NULL) {
		destruct_socket(client->socket);
		client->socket = NULL;
		printf("Disconnected from the server\n");
	}
	printf("Quit client\n");
	exit(0);
}