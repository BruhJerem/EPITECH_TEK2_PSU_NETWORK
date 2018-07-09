/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** parsing
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "server.h"

/**
* All the command in string
*/
static const char *function_command[] = {
	"USER", "NICK", "JOIN", "LIST", "PART",
	"NAMES", "PRIVMSG", "WHOIS", "QUIT"
};

/**
* Function pointer in array
*/
static bool (*fpts[])(server_t server, char **cmd, int index) = {
	user_registration, nick_registration, join, list, part, names, msg,
	whois, quit};

static bool find_command(server_t server, char **cmd, int current_index)
{
	if (!cmd[0])
		return true;
	for (int i = 0; function_command[i]; ++i) {
		if (!strcasecmp(function_command[i], cmd[0])) {
			printf("Command found : %s!\n", cmd[0]);
			fpts[i](server, cmd, current_index);
			return i == 8 ? false : true;
		}
	}
	return false;
}

static void dump_debug(server_t server)
{
	printf("-------------- USER in Server -------------------\n");
	client_dump(server->client_list);
	printf("-------------- Channel in Server -------------------\n");
	channel_dump(server->channel_list);
	printf("-------------- End of this proccess -------------------\n");
}

static channel_t get_channel_of_user(client_t current_client,
			channel_list_t tmp, char ***tab, char **buffer)
{
	channel_t channel;

	if (!strcmp(current_client->username, "*"))
		channel = channel_get_elem_by_name(tmp, "*");
	else
		channel = channel_get_elem_by_name(tmp,
				current_client->channel->name);
	if (!channel)
		return NULL;
	fix_buffer(*buffer);
	*tab = str_to_wordtab(*buffer, ' ');
	return channel;
}

bool parsing(server_t server, char *buffer, int idx)
{
	bool close_conn = false;
	char **tab;
	channel_list_t tmp = server->channel_list;
	client_list_t client_list = server->client_list;
	client_t current_client = client_get_elem_at_position(client_list, idx);
	channel_t channel;

	if (server->compress_fd || !buffer || !current_client)
		return false;
	channel = get_channel_of_user(current_client, tmp, &tab, &buffer);
	if (!tab || !channel)
		return false;
	printf("Message to send : [%s]\n", buffer);
	if (!find_command(server, tab, idx)) {
		if (!strcasecmp(tab[0], "QUIT"))
			close_conn = true;
	}
	free_tab(tab);
	dump_debug(server);
	return close_conn;
}
