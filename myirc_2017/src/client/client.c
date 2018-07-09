/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Client file
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <stdio.h>
#include "client.h"

static const char *command_tab[NBR_COMMANDS] = {
	"/server", "/list", "/users", "/disconnect",
	"/join", "/part", "/names",
	"/nick", "/msg", "/accept_file",
	"/help", "/quit"
};

static bool (*commands[NBR_COMMANDS])(client_t client, char **command) = {
	command_server, command_list, command_users, command_disconnect,
	command_join, command_part, command_names,
	command_nick, command_msg, command_accept_file,
	command_help, command_quit
};

void route_command(client_t client, char *buffer)
{
	char **command = str_to_wordtab(buffer, ' ');

	if (tab_len(command) == 0)
		return;
	if (command[0][0] != '/') {
		send_message(client, buffer);
		return;
	}
	if (check_server_connected(client, command[0]) == false)
		return;
	for (unsigned short i = 0; i <= NBR_COMMANDS - 1; i++) {
		if (strcasecmp(command_tab[i], command[0]) == 0) {
			commands[i](client, command);
			free_tab(command);
			return;
		}
	}
	printf("Command not found\n");
	free_tab(command);
}

client_t init_client(void)
{
	client_t client;

	client = malloc(sizeof(struct s_client));
	if (client == NULL)
		return NULL;
	client->socket = NULL;
	memset(client->fds, 0, sizeof(client->fds));
	client->fds[0].fd = STDIN_FILENO;
	client->fds[0].events = POLLIN;
	return client;
}

void client_loop(client_t client)
{
	int rc;

	client->nfds = 1;
	while (true) {
		rc = poll(client->fds, client->nfds, 3 * 60 * 1000);
		if (rc < 0)
			break;
		else if (rc == 0)
			break;
		handling_event(client);
	}
}
