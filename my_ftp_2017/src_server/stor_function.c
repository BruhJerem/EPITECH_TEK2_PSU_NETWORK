/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** stor_function
*/

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "server.h"
#include "lib/get_next_line.h"

static bool err_create_file(server_t *serv)
{
	write_to_client(serv, "550 Failed to create file.\n");
	return false;
}

static bool check_protocol(server_t *serv, const char *filename)
{
	if (serv->data_mode == NONE) {
		write_to_client(serv, "425 Use PORT or PASV first.\n");
		return false;
	}
	if (!filename) {
		return err_create_file(serv);
	}
	return true;
}

/**
* Check if stor do not exceed
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
	if (!strncmp(tmp, "/..", 3)) {
		return false;
	}
	return true;
}

/**
* Creation of file and fill it
* @param serv
* @param filename
* @return
*/

static bool creating_file(server_t *serv, const char *filename)
{
	FILE *fptr;
	char *buffer;

	if (directory_exists(filename) || check_root(serv, filename) == false) {
		return err_create_file(serv);
	}
	write_to_client(serv, "150 Opening ASCII mode data connection\n");
	fptr = fopen(filename, "w");
	if (!fptr) {
		return err_create_file(serv);
	}
	while ((buffer = get_next_line(serv->passv_fd))) {
		fprintf(fptr, "%s\n", buffer);
		free(buffer);
	}
	fclose(fptr);
	return true;
}

/**
* Upload file from client to server
* @param serv
* @param cmd
* @return
*/

bool stor_function(server_t *serv, char **cmd)
{
	if (!check_protocol(serv, cmd[1]))
		return false;
	printf("Current file creating: [%s]\n", cmd[1]);
	if (!creating_file(serv, cmd[1])) {
		return false;
	}
	close(serv->passv_fd);
	serv->data_mode = NONE;
	printf("[%s] : created and filled.\n", cmd[1]);
	write_to_client(serv, "226 Transfer complete.\n");
	return true;
}
