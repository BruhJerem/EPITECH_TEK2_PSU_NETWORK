/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** propagation
*/

#include <stdio.h>
#include "server.h"

bool nick_propagation(server_t server, client_t c_client, char *nick,
		      char **cmd)
{
	bool close_conn = false;
	client_t client = NULL;
	client_list_t client_in_channel = c_client->channel->client_list;

	for (; client_in_channel; client_in_channel = client_in_channel->next) {
		client = client_in_channel->client;
		if (!client || client->socket->fd <= 0 ||
		    client->status != LOGIN)
			continue;
		dprintf(client->socket->fd, RPL_NICK, c_client->nickname,
			c_client->username, server->socket->ip, nick, cmd[1]);
	}
	return close_conn;
}

bool join_propagation(server_t server, client_t c_client, char **cmd)
{
	bool close_conn = false;
	client_t client = NULL;
	client_list_t client_in_channel =
		c_client->channel->client_list;

	for (; client_in_channel; client_in_channel = client_in_channel->next) {
		client = client_in_channel->client;
		if (!client || client->socket->fd <= 0 ||
		    client->status != LOGIN ||
			client->socket->fd == c_client->socket->fd)
			continue;
		dprintf(client->socket->fd, RPL_JOIN, c_client->nickname,
			c_client->username,
			server->socket->ip, cmd[1]);
	}
	return close_conn;
}

bool part_propagation(server_t server, client_t c_client, char **cmd)
{
	bool close_conn = false;
	client_t client = NULL;
	client_list_t client_in_channel =
		c_client->channel->client_list;

	for (; client_in_channel; client_in_channel = client_in_channel->next) {
		client = client_in_channel->client;
		if (!client || client->socket->fd <= 0 ||
		    client->status != LOGIN)
			continue;
		dprintf(client->socket->fd, RPL_PART, c_client->nickname,
			c_client->username,
			server->socket->ip, cmd[1]);
	}
	return close_conn;
}