/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** GUI client command router
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static const char *function_command_ui[] = {
	"msz", "bct", "mct", "tna", "ppo", "plv", "pin", "sgt", "sst"
};

static bool (*fpts_ui[])(server_t server, char **cmd, int index) = {
	msz, bct, mct, tna, ppo, plv, pin, sgt, sst
};

bool route_command_ui(server_t server, char **cmd, int index)
{
	if (!cmd[0])
		return true;
	for (int i = 0; function_command_ui[i]; ++i) {
		if (!strcmp(function_command_ui[i], cmd[0])) {
			printf("[GUI CMD] Found : %s\n", cmd[0]);
			fpts_ui[i](server, cmd, index);
			return true;
		}
	}
	dprintf(server->poll_fds[index].fd, "ko\n");
	return false;
}
