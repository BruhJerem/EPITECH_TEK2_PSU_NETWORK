/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Check
*/

#include <unistd.h>
#include <stdbool.h>
#include <server.h>
#include <strings.h>
#include <stdio.h>

bool check_server_connected(client_t client, char *start_cmd)
{
	if (strcasecmp("/server", start_cmd) != 0 && strcasecmp("/help",
		start_cmd) != 0 && strcasecmp("/quit", start_cmd) != 0) {
		if (client->socket == NULL) {
			printf("To send command, please connect to a server\n");
			return false;
		}
	}
	return true;
}
