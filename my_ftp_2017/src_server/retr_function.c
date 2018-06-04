/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** data_transfert
*/

#include <string.h>
#include <zconf.h>
#include <stdio.h>
#include "server.h"

static bool check_protocol(server_t *serv)
{
	if (serv->data_mode == NONE) {
		write_to_client(serv, "425 Use PORT or PASV first.\n");
		return false;
	}
	return true;
}

/**
* Give byte of file
* @param f
* @return
*/

static long get_byte_file(FILE *f)
{
	long size;

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
}

/**
* Read file given in param
* @param serv
* @param filename
* @return
*/

static bool read_file(server_t *serv, const char *filename)
{
	FILE *file;
	int c;

	file = fopen(filename, "r");
	if (!file) {
		printf("Current file sending: [%s]\n", filename);
		write_to_client(serv, "550 Failed to open file.\n");
		return false;
	}
	dprintf(serv->client_fd, "150 Opening ASCII mode data connection for "
		"%s (%zu bytes).\n", filename, get_byte_file(file));
	while ((c = getc(file)) != EOF) {
		dprintf(serv->passv_fd, "%c", c);
	}
	fclose(file);
	return true;
}

/**
* Check if retr do not exceed
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
* Download file from server to client
* @param serv
* @param cmd
* @return true if no error
*/

bool retr_function(server_t *serv, char **cmd)
{
	if (!check_protocol(serv))
		return false;
	printf("Current file sending: [%s]\n", cmd[1]);
	if (!cmd[1] || is_regular_file(cmd[1]) == false ||
		check_root(serv, cmd[1]) == false) {
		write_to_client(serv, "550 Failed to open file.\n");
		return false;
	}
	if (!read_file(serv, cmd[1])) {
		return false;
	}
	close(serv->passv_fd);
	serv->data_mode = NONE;
	write_to_client(serv, "226 Transfer complete.\n");
	return true;
}