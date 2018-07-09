/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** send_client
*/

#include <stdio.h>
#include "server.h"

bool send_to_client_from_channel(char *buffer,
					server_t server, channel_t channel,
					client_t c_client)
{
	client_list_t client_in_channel = channel->client_list;
	client_t client;
	bool close_conn = false;


	for (; client_in_channel; client_in_channel = client_in_channel->next) {
		client = client_in_channel->client;
		if (!client || client->socket->fd <= 0 ||
			client->status != LOGIN || client->socket->fd ==
							c_client->socket->fd)
			continue;
		dprintf(client->socket->fd, RPL_PRIVMSG, client->nickname,
			client->username, server->socket->ip,
			c_client->nickname, buffer);
	}
	return close_conn;
}

static char *get_buffer(char **cmd)
{
	if (tab_len(cmd) < 2)
		return NULL;
	for (int i = 2; cmd[i]; i++) {
		if (cmd[i][0] == ':')
			return &rebind(&cmd[i], ' ')[1];
	}
	return NULL;
}

bool send_to_nick(server_t server, char **cmd, client_t to_client,
	client_t client)
{
	char *buffer = get_buffer(cmd);
	int rc;

	if (!buffer) {
		dprintf(client->socket->fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return true;
	}
	rc = dprintf(to_client->socket->fd, RPL_PRIVMSG, to_client->nickname,
		to_client->username, server->socket->ip,
		client->nickname, buffer);
	if (rc < 0) {
		perror("  dprintf() failed");
		return true;
	}
	return false;
}
