/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Command router (dispatcher)
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "lib-tools.h"

bool command_router(server_t server, char *buffer, size_t idx)
{
	bool close_conn = false;
	char **cmd = str_to_wordtab(buffer, ' ');

	printf("Request received : [%s]\n", buffer);
	if (server->ui && server->poll_fds[idx].fd == server->ui->socket->fd)
		route_command_ui(server, cmd, (int) idx);
	else
		route_command_player(server, cmd, (int) idx);
	if (cmd)
		free(cmd);
	//debug_server(server);
	return close_conn;
}
