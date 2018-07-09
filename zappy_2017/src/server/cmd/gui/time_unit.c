/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Time unit ui cmd function
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib-tools.h"
#include "server.h"

bool sgt(server_t server, char **cmd, int index)
{
	int fd = server->poll_fds[index].fd;
	(void) cmd;

	dprintf(fd, C_SGT, server->action_freq);
	return true;
}

bool sst(server_t server, char **cmd, int index)
{
	ushort_t frequency = server->action_freq;
	(void) cmd;
	(void) index;

	if (tab_len(cmd) < 2 || !str_is_number(cmd[1])) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	frequency = (ushort_t) atoi(cmd[1]);
	server->action_freq = frequency;
	return true;
}
