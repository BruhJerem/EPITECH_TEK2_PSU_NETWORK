/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** list_function
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include "server.h"

/**
* Check current protocol used
* @param serv
* @param file
* @return
*/

static bool check_protocol(server_t *serv, const char *file)
{
	if (serv->data_mode == NONE) {
		write_to_client(serv, "425 Use PORT or PASV first.\n");
		return false;
	}
	write_to_client(serv, "150 Here comes the directory listing.\n");
	if (!file)
		return true;
	return true;
}

/**
* Print the command ls
* @param file
* @param serv
*/

static void print_list(FILE *file, server_t *serv)
{
	int c;

	if (file) {
		while ((c = getc(file)) != EOF) {
			dprintf(serv->passv_fd, "%c", c);
		}
		fclose(file);
	} else
		printf("FIle do not exists\n");
}

/**
* Check if ls before root
* @param serv
* @param path
* @param ls_command
* @return
*/

static char *check_root(server_t *serv, char *path, char *ls_command)
{
	char *tmp;
	char command[1024] = "ls -l ";

	if (!path) {
		return ls_command;
	}
	if (!strcmp(serv->path->home, serv->path->curr)) {
		tmp = strdup(serv->path->home +
			strlen(serv->path->home) - 1);
	} else {
		tmp = strdup(serv->path->curr +
			strlen(serv->path->home) - 1);
	}
	strcat(tmp, path);
	if (tmp[strlen(serv->path->curr)-strlen(serv->path->home)+2] == '.') {
		ls_command = strcat(command, serv->path->home);
	} else
		ls_command = strcat(ls_command, path);
	ls_command = strcat(ls_command, "\0");
	return ls_command;
}

/**
* LIST Function
* @param serv
* @param cmd
* @return
*/

bool list_function(server_t *serv, char **cmd)
{
	FILE *file;
	char command[1024] = "ls -l ";
	char *ls_command = strcat(command, serv->path->curr);

	if (!check_protocol(serv, cmd[1]))
		return false;
	ls_command = check_root(serv, cmd[1], ls_command);
	printf("Current command %s\n", ls_command);
	file = popen(ls_command, "r");
	print_list(file, serv);
	close(serv->passv_fd);
	serv->data_mode = NONE;
	write_to_client(serv, "226 Directory send OK.\n");
	return true;
}