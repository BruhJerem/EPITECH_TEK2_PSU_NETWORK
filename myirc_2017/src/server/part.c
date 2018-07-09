/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** part
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static channel_t check_channel(server_t server, char **cmd, client_t client)
{
	channel_list_t channel_list = server->channel_list;
	channel_t channel;

	if (!cmd[1]) {
		dprintf(client->socket->fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return NULL;
	}
	channel = channel_get_elem_by_name(channel_list, cmd[1]);
	if (!channel) {
		dprintf(client->socket->fd, ERR_NOSUCHCHANNEL,
			server->socket->ip, client->nickname, cmd[1]);
		return NULL;
	}
	if (!strcmp(client->channel->name, cmd[1]))
		return channel;
	dprintf(client->socket->fd, ERR_NOTONCHANNEL, server->socket->ip,
	client->nickname);
	return NULL;
}

bool part(server_t server, char **cmd, int index)
{
	client_list_t client_list = server->client_list;
	client_t client = client_get_elem_at_position(client_list,
						      (unsigned int) index);
	channel_t channel = check_channel(server, cmd, client);
	channel_list_t tmp = server->channel_list;
	channel_t global_channel = channel_get_elem_by_name(tmp, "*");
	client_list_t t;

	if (!channel)
		return true;
	part_propagation(server, client, cmd);
	client->channel = global_channel;
	t = global_channel->client_list;
	client_add_elem_at_back(t, client);
	t = channel->client_list;
	client_del_elem_by_name(t, client->username);
	return true;
}
