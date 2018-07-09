/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** names
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static bool check_status(client_t client)
{
	if (client->status != LOGIN)
		return false;
	return true;
}

static channel_t check_channel(client_t client, channel_list_t tmp, char **cmd)
{
	channel_t current_channel;

	if (!check_status(client))
		return NULL;
	if (!cmd[1])
		current_channel = channel_get_elem_by_name(tmp,
					client->channel->name);
	else
		current_channel = channel_get_elem_by_name(tmp, cmd[1]);
	if (!current_channel)
		return NULL;
	return current_channel;
}

static bool dump_names(server_t server, client_list_t ch_client_list,
		client_t client)
{
	bool close_conn = false;
	client_t cl;
	char b[255] = "\0";

	for (; ch_client_list; ch_client_list = ch_client_list->next) {
		cl = ch_client_list->client;
		if (cl->nickname[0] == '\0')
			continue;
		sprintf(b, "%s%s", b, cl->nickname);
		if (ch_client_list->next)
			sprintf(b, "%s ", b);
	}
	dprintf(client->socket->fd, RPL_NAMREPLY,
		server->socket->ip, client->nickname,
		client->channel->name, b);
	return close_conn;
}

bool names(server_t server, char **cmd, int index)
{
	channel_list_t tmp = server->channel_list;
	channel_t current_channel;
	client_list_t client_list = server->client_list;
	client_t client = client_get_elem_at_position(client_list, index);
	client_list_t ch_client_list;
	bool close_conn;

	current_channel = check_channel(client, tmp, cmd);
	if (!current_channel)
		return false;
	ch_client_list = current_channel->client_list;
	close_conn = dump_names(server, ch_client_list, client);
	dprintf(client->socket->fd, RPL_ENDOFNAMES, server->socket->ip,
		client->nickname, client->channel->name);
	return close_conn;
}
