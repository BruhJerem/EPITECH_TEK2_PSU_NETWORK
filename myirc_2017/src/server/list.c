/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** list
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static bool check_status(server_t server, client_t client)
{
	if (client->status != LOGIN)
		return false;
	dprintf(client->socket->fd, RPL_LISTSTART, server->socket->ip,
		client->nickname);
	return true;
}

static void dump_list_common(server_t server, client_t client,
				channel_list_t tmp, char *cmd)
{
	char ch[30];

	sprintf(ch, "*%s*", cmd);
	for (; tmp; tmp = tmp->next) {
		if (nmatch(tmp->channel->name, ch) == 1) {
			dprintf(client->socket->fd, RPL_LIST,
				server->socket->ip,
				client->nickname, tmp->channel->name);
		}
	}
}

static bool dump_list(server_t server, client_t client, channel_list_t tmp)
{
	int rc;
	bool close_conn = false;

	for (; tmp; tmp = tmp->next) {
		if (!strcmp("global", tmp->channel->name))
			continue;
		rc = dprintf(client->socket->fd, RPL_LIST,
			server->socket->ip,
			client->nickname, tmp->channel->name);
		if (rc < 0) {
			perror("  dprintf() failed");
			close_conn = true;
		}
	}
	return close_conn;
}

bool list(server_t server, char **cmd, int index)
{
	channel_list_t tmp = server->channel_list;
	client_list_t client_list = server->client_list;
	client_t client = client_get_elem_at_position(client_list,
		(unsigned int) index);
	bool close_conn = false;

	if (!check_status(server, client))
		return true;
	if (cmd[1])
		dump_list_common(server, client, tmp, cmd[1]);
	else
		close_conn = dump_list(server, client, tmp);
	dprintf(client->socket->fd, RPL_LISTEND,
		server->socket->ip, client->nickname);
	return close_conn;
}
