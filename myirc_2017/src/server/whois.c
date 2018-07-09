/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** whois
*/

#include <stdio.h>
#include "server.h"

static client_t find_by_nickname(server_t server, char *nickname)
{
	client_list_t tmp = server->client_list;
	client_t client = client_get_elem_by_nick(tmp, nickname);

	return client;
}

bool whois(server_t server, char **cmd, int index)
{
	client_list_t client_list = server->client_list;
	client_t current_cl = client_get_elem_at_position(client_list, index);
	client_t who_is_client;

	if (!cmd[1]) {
		dprintf(current_cl->socket->fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, current_cl->nickname);
		return false;
	}

	who_is_client = find_by_nickname(server, cmd[1]);
	if (!who_is_client) {
		dprintf(current_cl->socket->fd, ERR_NOSUCHNICK,
			server->socket->ip, current_cl->nickname);
		return false;
	}
	dprintf(current_cl->socket->fd, RPL_WHOISUSER, server->socket->ip,
		current_cl->nickname, who_is_client->nickname,
		who_is_client->username, who_is_client->realname);
	return true;
}
