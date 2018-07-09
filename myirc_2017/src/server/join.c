/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** join
*/

#include "server.h"
#include <string.h>
#include <stdio.h>

static void pop_user(server_t server, client_t current_client,
			channel_t channel)
{
	client_list_t channel_client_list;
	channel_t channel2;
	channel_list_t channel_list = server->channel_list;

	channel2 = channel_get_elem_by_name(channel_list,
					current_client->channel->name);
	channel_client_list = channel2->client_list;
	client_del_elem_by_name(channel_client_list, current_client->username);
	current_client->channel = channel;
	channel_client_list = channel->client_list;
	client_add_elem_at_back(channel_client_list, current_client);
}

static bool check_channel(server_t server, client_t client, char *name, int i)
{
	if (name[0] != '#' && name[0] != '&') {
		dprintf(server->fds[i].fd, ERR_NOSUCHCHANNEL,
			server->socket->ip, client->nickname, name);
		return false;
	}
	return true;
}

static bool dump_names(server_t server, client_list_t ch_client_list,
			client_t client)
{
	bool close_conn = false;
	client_t cl;
	char b[255] = "\0";

	if (!ch_client_list->next)
		return false;
	ch_client_list = ch_client_list->next;
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
	dprintf(client->socket->fd, RPL_ENDOFNAMES, server->socket->ip,
		client->nickname, client->channel->name);
	return close_conn;
}

bool join(server_t server, char **cmd, int index)
{
	client_list_t list = server->client_list;
	client_t c_client = client_get_elem_at_position(list,
						(unsigned int) index);
	channel_list_t channel_list = server->channel_list;
	channel_t channel = channel_get_elem_by_name(channel_list, cmd[1]);

	if (!c_client || c_client->status != LOGIN || !check_channel(server,
		c_client, cmd[1], index)) {
		return false;
	}
	if (!channel) {
		channel = create_channel(cmd[1], PUBLIC);
		channel_add_elem_at_back(channel_list, channel);
	}
	pop_user(server, c_client, channel);
	dprintf(server->fds[index].fd, RPL_JOIN, c_client->nickname,
		c_client->username,
		server->socket->ip, cmd[1]);
	dump_names(server, channel->client_list, c_client);
	join_propagation(server, c_client, cmd);
	return true;
}
