/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** registration
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "server.h"

static bool check_param(server_t server, client_t client, char **cmd, int idx)
{
	int i = (int) tab_len(cmd);

	if (i > 5) {
		if (cmd[4][0] == ':')
			return true;
		dprintf(server->fds[idx].fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return false;
	} else if (i < 5) {
		dprintf(server->fds[idx].fd, ERR_NEEDMOREPARAMS,
			server->socket->ip, client->nickname);
		return false;
	}
	return true;

}

static void set_name(server_t server, client_t client, char **cmd)
{
	char *r_name;

	strcpy(client->username, strdup(cmd[1]));
	if (client->status == ENTER_USER) {
		client->status = LOGIN;
		print_welcome(server, client);
	} else if (client->status == LOGOUT)
		client->status = ENTER_USER;
	if (cmd[4][0] == ':')
		r_name = &rebind(&cmd[4], ' ')[1];
	else
		r_name = cmd[4];
	strcpy(client->realname, r_name);
}

static bool check_status(server_t server, client_t client, int index,
			char **cmd)
{
	(void)cmd;
	if (client->status == LOGIN) {
		dprintf(server->fds[index].fd, ERR_ALREADYREGISTERED,
			server->socket->ip, client->nickname);
		return false;
	}
	return true;
}

bool user_registration(server_t server, char **cmd, int index)
{
	client_list_t tmp = server->client_list;
	client_t client = client_get_elem_at_position(tmp, index);
	channel_list_t tm = server->channel_list;
	channel_t ch = channel_get_elem_by_name(tm, "*");
	client_list_t list;

	if (!client || !check_param(server, client, cmd, index))
		return false;
	if (!check_status(server, client, index, cmd))
		return false;
	set_name(server, client, cmd);
	printf(" USER command : SUCCESS : %s\n", client->nickname);
	client->channel = ch;
	list = ch->client_list;
	client_add_elem_at_back(list, client);
	return true;
}
