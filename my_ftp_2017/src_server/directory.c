/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** pwd_function
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>
#include "server.h"

static bool print_err_dir(server_t *serv)
{
	write_to_client(serv, "550 Failed to change directory.\n");
	return false;
}

/**
* Function to go back to home
* @param serv
* @param cmd
* @return
*/

bool cdup_function(server_t *serv, char **cmd)
{
	(void)cmd;
	if (chdir(serv->path->home) == -1) {
		return print_err_dir(serv);
	}
	serv->path->curr = strdup(serv->path->home);
	write_to_client(serv, "250 Directory successfully changed.\n");
	printf("Current full path: %s\n", serv->path->curr);
	return true;
}

/**
* Check to dont go before root
* @param serv
* @param path
* @return
*/

static bool check_root(server_t *serv, const char *path)
{
	char *tmp;

	if (!strcmp(serv->path->home, serv->path->curr)) {
		tmp = strdup(serv->path->home +
			strlen(serv->path->home) - 1);
	} else {
		tmp = strdup(serv->path->curr +
			strlen(serv->path->home) - 1);
	}
	strcat(tmp, path);
	if (tmp[strlen(serv->path->curr)-strlen(serv->path->home)+2] == '.') {
		return false;
	}
	return true;
}

/**
* Moove to directory
* @param serv
* @param cmd
* @return
*/

bool cwd_function(server_t *serv, char **cmd)
{
	char cwd[size_current_path()];

	if (!cmd[1])
		return print_err_dir(serv);
	if (check_root(serv, cmd[1])) {
		if (chdir(cmd[1]) == -1) {
			return print_err_dir(serv);
		}
		serv->path->curr = getcwd(cwd, sizeof(cwd));
		serv->path->curr =
			strcat(serv->path->curr, "/\0");
	} else {
		if (chdir(serv->path->home) == -1) {
			return print_err_dir(serv);
		}
		serv->path->curr = serv->path->home;
	}
	write_to_client(serv, "250 Directory successfully changed.\n");
	printf("Current full path: %s\n", serv->path->curr);
	return true;
}

/**
* Show current path
* @param serv
* @param cmd
* @return
*/

bool pwd_function(server_t *serv, char **cmd)
{
	char *tmp;

	(void)cmd;
	if (!strcmp(serv->path->home, serv->path->curr)) {
		tmp = strdup(serv->path->home +
			strlen(serv->path->home) - 1);
	} else {
		tmp = strdup(serv->path->curr +
			strlen(serv->path->home) - 1);
	}
	dprintf(serv->client_fd, "257 \"%s\"\n", tmp);
	printf("PWD Function called.\n");
	free(tmp);
	return true;
}