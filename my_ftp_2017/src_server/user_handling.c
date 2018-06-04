/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** user_handling
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

/**
* Check if username and pasw correspond to Anonymous and EMPTY
* @param serv
* @return
*/

static bool check_matching(server_t *serv)
{
	if (!strcasecmp(serv->connection->usename_cmd, USERNAME) &&
	serv->connection->password_cmd == NULL) {
		write_to_client(serv, "230 Login successful.\n");
		serv->connection->is_connected = COMPLETE;
		return true;
	}
	serv->connection->is_connected = EMPTY;
	write_to_client(serv, "530 Login incorrect.\n");
	return false;
}

static bool print_perm(server_t *serv)
{
	write_to_client(serv, "530 Permission denied.\n");
	return false;
}

static bool handling_username(server_t *serv, char **cmd)
{
	if ((serv->connection->is_connected == EMPTY ||
		serv->connection->is_connected == USER) &&
		cmd[1] == NULL && strcasecmp(cmd[0], "pass") != 0) {
		return print_perm(serv);
	}
	if ((serv->connection->is_connected == EMPTY ||
		serv->connection->is_connected == USER) &&
		!strcasecmp(cmd[0], "user")) {
		if (!cmd[1]) {
			return print_perm(serv);
		}
		if (serv->connection->usename_cmd)
			free(serv->connection->usename_cmd);
		serv->connection->usename_cmd = strdup(cmd[1]);
		write_to_client(serv, "331 Please specify the password.\n");
		serv->connection->is_connected = USER;
		return false;
	}
	return true;
}

/**
* Specify user & password for authentication
* @param serv
* @param cmd
* @return
*/

bool handling_user_connection(server_t *serv, char **cmd)
{
	if (!check_status(serv, cmd))
		return false;
	if (!handling_username(serv, cmd)) {
		return false;
	} else if (serv->connection->is_connected == USER &&
		!strcasecmp(cmd[0], "pass")) {
		serv->connection->password_cmd = cmd[1] ? strdup(cmd[1])
							: NULL;
		serv->connection->is_connected = READY;
	}
	if (serv->connection->is_connected == READY) {
		if (!check_matching(serv))
			return false;
	}
	return true;
}
