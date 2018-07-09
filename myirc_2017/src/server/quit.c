/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** quit
*/

#include <stdio.h>
#include "server.h"

bool handle_disconnect(server_t server, int index)
{
	client_list_t tmp = server->client_list;
	channel_list_t channel_list = server->channel_list;
	client_t client = client_get_elem_at_position(tmp, index);
	channel_t channel;
	client_list_t ch_client_list;

	if (!client)
		return true;
	channel = channel_get_elem_by_name(channel_list,
					client->channel->name);
	if (channel) {
		ch_client_list = channel->client_list;
		client_del_elem_by_name(ch_client_list, client->username);
	}
	tmp = server->client_list;
	client_del_elem_at_position(tmp, index);
	printf("Connection closed\n");
	return true;
}

bool quit(server_t server, char **cmd, int index)
{
	(void) cmd;
	return handle_disconnect(server, index);
}
