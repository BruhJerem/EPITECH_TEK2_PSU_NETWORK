/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player client command router
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static const char *function_command_player[] = {
	BROADCAST_TEXT, EJECT, FORK, FORWARD, INCANTATION, LIST_INVENTORY,
	LEFT, LOOK, RIGHT, SET_OBJ, TAKE_OBJ, CONNECT
};

static bool (*fpts_player[])(server_t server, char **cmd, int index) = {
	broadcast_text, eject, fork_player, forward, incantation, inventory,
	left, look, right, set_object, take_object, connect_player
};

bool route_command_player(server_t server, char **cmd, int index)
{
	if (!cmd[0])
		return true;
	for (int i = 0; function_command_player[i]; i++) {
		if (!strcmp(function_command_player[i], cmd[0])) {
			printf("[Player CMD] Found : %s\n", cmd[0]);
			fpts_player[i](server, cmd, index);
			return true;
		}
	}
	dprintf(server->poll_fds[index].fd, "ko\n");
	return false;
}
