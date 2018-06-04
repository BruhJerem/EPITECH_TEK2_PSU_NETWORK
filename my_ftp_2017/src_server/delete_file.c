/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** delete_file
*/

#include "server.h"
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <zconf.h>

/**
* Check if file in path is regular file
* @param path
* @return
*/

int is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode)) {
		if (access(path, R_OK) == 0) {
			return true;
		}
		return false;
	}
	return false;
}

/**
* Check if file is before root
* @param serv
* @param filename
* @return
*/

bool check_before(server_t *serv, const char *filename)
{
	char *tmp;

	if (!strcmp(serv->path->home, serv->path->curr)) {
		tmp = strdup(serv->path->home +
			strlen(serv->path->home) - 1);
	} else {
		tmp = strdup(serv->path->curr +
			strlen(serv->path->home) - 1);
	}
	strcat(tmp, filename);
	if (tmp[strlen(serv->path->curr)-strlen(serv->path->home)+2] == '.') {
		write_to_client(serv, "550 Permission denied.\n");
		return false;
	}
	return true;
}

/**
* Delete file on the server
* @param serv
* @param cmd
* @return
*/

bool dele_function(server_t *serv, char **cmd)
{
	int ret;

	if (!cmd[1] || !is_regular_file(cmd[1]) ||
		!check_before(serv, cmd[1])) {
		write_to_client(serv, "550 Permission denied.\n");
		return false;
	}
	ret = remove(cmd[1]);
	if (ret == 0) {
		write_to_client(serv, "250 Requested file action okay, "
			"completed.\n");
	} else {
		write_to_client(serv, "550 Permission denied.\n");
		return false;
	}
	return true;
}