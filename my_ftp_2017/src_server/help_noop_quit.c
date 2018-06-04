/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** help_noop
*/

#include <zconf.h>
#include <stdlib.h>
#include "server.h"

/**
* Do nothing
* @param serv
* @param cmd
* @return
*/

bool noop_function(server_t *serv, char **cmd)
{
	(void)cmd;
	if (!write_to_client(serv, "200 NOOP ok.\n"))
		return false;
	return true;
}

/**
* Disconnect
* @param serv
* @param cmd
* @return
*/

bool quit_function(server_t *serv, char **cmd)
{
	(void)cmd;
	serv->connection->is_connected = EMPTY;
	serv->connection->usename_cmd = NULL;
	serv->connection->password_cmd = NULL;
	if (!write_to_client(serv, "221 Goodbye.\n"))
		return false;
	free(serv->connection);
	free(serv->path);
	close(serv->client_fd);
	return true;
}

/**
* Print help
* @param serv
* @param cmd
* @return
*/

bool help_function(server_t *serv, char **cmd)
{
	(void)cmd;
	if (!write_to_client(serv, "214-The following commands are recognized."
		"\nUSER PASS CWD CDUP QUIT DELE PWD PASV PORT HELP NOOP \n"
		"RETR STOR LIST\n"
		"214 Help OK.\n"))
		return false;
	return true;
}