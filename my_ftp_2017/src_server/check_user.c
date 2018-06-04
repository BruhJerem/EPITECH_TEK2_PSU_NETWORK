/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** check_user
*/

#include <string.h>
#include "server.h"

/**
* Check if user is connected or not
* @param serv
* @param cmd
* @return
*/

bool check_connected(server_t *serv, char *cmd)
{
	if (serv->connection->is_connected != COMPLETE) {
		if (!strcasecmp("pass", cmd)) {
			write_to_client(serv, "503 Login with USER first.\n");
			return false;
		}
		write_to_client(serv, "530 Please login with "
			"USER and PASS.\n");
		return false;
	}
	return true;
}

/**
* Check if user is connected
* @param serv
* @param cmd
* @return
*/

bool check_status(server_t *serv, char **cmd)
{
	if (serv->connection->is_connected == COMPLETE) {
		if (!strcasecmp(cmd[0], "pass"))
			write_to_client(serv, "230 Already logged in.\n");
		if (!strcasecmp(cmd[0], "user"))
			write_to_client(serv,
					"530 Can't change from guest user.\n");
		return false;
	}
	if (!strcasecmp(cmd[0], "pass") &&
		serv->connection->is_connected != USER) {
		write_to_client(serv, "503 Login with USER first.\n");
		return false;
	}
	return true;
}