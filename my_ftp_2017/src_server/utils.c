/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** utils
*/

#include <zconf.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <asm/errno.h>
#include <errno.h>
#include "server.h"

/**
* Check if directory exist
* @param filename
* @return
*/

bool directory_exists(const char * filename)
{
	DIR *dir = opendir(filename);

	if (dir) {
		closedir(dir);
		return true;
	}
	return false;
}

/**
* Give size of current path
* @return
*/

size_t size_current_path(void)
{
	long path_max;
	size_t size;

	path_max = pathconf(".", _PC_PATH_MAX);
	if (path_max == -1)
		size = 1024;
	else if (path_max > 10240)
		size = 10240;
	else
		size = path_max;
	return size;
}

/**
* Give the full path of current Home
* @param serv
* @param path
* @return
*/

bool find_home_path(server_t *serv, const char *path)
{
	char cwd[size_current_path()];

	serv->path->home = getcwd(cwd, sizeof(cwd));
	serv->path->home = strcat(serv->path->home, "/\0");
	serv->path->home = strcat(serv->path->home, path);
	if (serv->path->home[strlen(serv->path->home) - 1] != '/')
		serv->path->home = strcat(serv->path->home, "/\0");
	printf("HOME : %s\n", serv->path->home);
	return true;
}