/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map ui cmd function
*/

#include <lib-tools.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

bool bct(server_t server, char **cmd, int index)
{
	int x = 0;
	int y = 0;
	int rc;

	if (tab_len(cmd) < 2) {
		dprintf(server->poll_fds[index].fd, C_ARGUMENT_ERROR);
		return false;
	}
	x = atoi(cmd[1]);
	y = atoi(cmd[2]);
	rc = get_tile_index(server->map, y, x);
	if (rc < 0) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	send_tile_inventory(server->map->tiles[rc], server->poll_fds[index].fd);
	return true;
}

bool msz(server_t server, char **cmd, int index)
{
	map_t map = server->map;
	(void) cmd;

	dprintf(server->poll_fds[index].fd, C_MSZ, map->width, map->height);
	return true;
}

bool mct(server_t server, char **cmd, int index)
{
	int fd = server->poll_fds[index].fd;
	(void) cmd;

	send_tiles_inventory(server, fd);
	return true;
}
