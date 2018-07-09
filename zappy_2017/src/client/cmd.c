/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Default commands IA
*/

#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include "client.h"

bool send_cmd(t_client *client, const char *cmd)
{
	printf(DEBUG, cmd, client->fd);
	if (!dprintf(client->fd, "%s\n", cmd))
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	return true;
}

bool cmd_ok(const char *str)
{
	return strcmp(str, EXPECTED_ANSWER) != 0 ? false : true;
}

bool cmd_ko(const char *str)
{
	return strcmp(str, UNEXPECTED_ANSWER) != 0 ? false : true;
}

bool is_dead(const char *str)
{
	return strcmp(str, DEAD) != 0 ? false : true;
}
