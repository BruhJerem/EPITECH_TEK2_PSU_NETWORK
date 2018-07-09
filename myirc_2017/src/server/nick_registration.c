/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** nick_registration
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

static bool check_nickname_in_use(server_t server, char *nick, int index)
{
	client_list_t tmp = server->client_list;

	if (!strcmp("*", nick))
		return true;
	while (tmp) {
		if (!strcmp(tmp->client->nickname, nick)) {
			dprintf(server->fds[index].fd, ERR_NICKNAMEINUSE,
				server->socket->ip, nick);
			return false;
		}
		tmp = tmp->next;
	}
	return true;
}

void print_welcome(server_t server, client_t client)
{
	if (client->status == LOGIN) {
		dprintf(client->socket->fd, RPL_WELCOME, server->socket->ip,
			client->nickname);
		dprintf(client->socket->fd, RPL_MOTDSTART,
			server->socket->ip, client->nickname);
		dprintf(client->socket->fd, RPL_MOTD,
			server->socket->ip, client->nickname);
		dprintf(client->socket->fd, RPL_ENDOFMOTD,
			server->socket->ip, client->nickname);
	}
}

static bool check_param(server_t server, client_t client, char **cmd, int index)
{
	if (tab_len(cmd) > 2) {
		dprintf(server->fds[index].fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return false;
	}
	if (!cmd[1]) {
		dprintf(server->fds[index].fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return false;
	}
	return true;
}

bool nick_registration(server_t server, char **cmd, int index)
{
	client_list_t tmp = server->client_list;
	client_t client = client_get_elem_at_position(tmp, index);
	char *tmp_nick = strdup(client->nickname);

	if (!check_param(server, client, cmd, index))
		return false;
	if (!check_nickname_in_use(server, cmd[1], index))
		return false;
	strcpy(client->nickname, cmd[1]);
	if (client->status == ENTER_USER) {
		client->status = LOGIN;
		print_welcome(server, client);
	} else if (client->status == LOGOUT)
		client->status = ENTER_USER;
	if (strcmp(tmp_nick, "*") != 0)
		nick_propagation(server, client, tmp_nick, cmd);
	free(tmp_nick);
	printf(" NICK command : SUCCESS for NICKNAME: %s\n", client->nickname);
	return true;
}
