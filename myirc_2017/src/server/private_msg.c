/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** private_msg
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static channel_t get_channel_of_client(server_t server, client_t client)
{
	channel_t channel;
	channel_list_t tmp = server->channel_list;

	if (!strcmp(client->username, "*"))
		channel = channel_get_elem_by_name(tmp, "*");
	else
		channel = channel_get_elem_by_name(tmp, client->channel->name);
	if (!channel)
		return NULL;
	return channel;
}

static bool check_if_channel(server_t server, char **cmd, client_t client)
{
	char *buffer = rebind(&cmd[2], ' ');
	channel_list_t channel_servers = server->channel_list;
	channel_t channel_from_cmd = channel_get_elem_by_name(channel_servers,
					cmd[1]);
	channel_t channel = get_channel_of_client(server, client);

	if (!channel_from_cmd)
		return false;
	send_to_client_from_channel(&buffer[1], server, channel, client);
	return true;
}

bool msg(server_t server, char **cmd, int index)
{
	client_list_t tmp = server->client_list;
	client_t to_client = client_get_elem_by_nick(tmp, cmd[1]);
	client_t current_client;

	tmp = server->client_list;
	current_client = client_get_elem_at_position(tmp, index);
	if (!to_client || to_client->status != LOGIN) {
		if (check_if_channel(server, cmd, current_client))
			return true;
		dprintf(current_client->socket->fd, ERR_NOSUCHNICK,
			server->socket->ip, current_client->nickname);
		return false;
	}
	return send_to_nick(server, cmd, to_client, current_client);
}
