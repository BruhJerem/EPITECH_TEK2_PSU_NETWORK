/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Team ui cmd function
*/

#include <stdio.h>
#include "server.h"

bool tna(server_t server, char **cmd, int index)
{
	(void) cmd;

	send_teams(server, server->poll_fds[index].fd);
	return true;
}
