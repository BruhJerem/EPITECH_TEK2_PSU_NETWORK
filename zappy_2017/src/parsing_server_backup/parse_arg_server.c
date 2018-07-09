/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Parse args
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <server.h>
#include "parse_server.h"

static bool is_port(const char *flag, const char *arg, server_t **server)
{
	if ((*server)) {
		exit(EXIT_FAILURE);
	}
	if (!strcmp(flag, SHORT_FLAG_PORT) || !strcmp(flag, LONG_FLAG_PORT)) {
		if (!port_server(arg, server)) {
			exit(EXIT_FAILURE);
		}
		return true;
	}
	return false;
}

static bool is_width(const char *flag, const char *arg, server_t **server)
{
	if (!strcmp(flag, FLAG_WIDTH)) {
		if (!width_server(arg, server)) {
			exit(EXIT_FAILURE);
		}
		return true;
	}
	return false;
}

static bool is_height(const char *flag, const char *arg, server_t **server)
{
	if (!strcmp(flag, FLAG_HEIGHT)) {
		if (!height_server(arg, server)) {
			exit(EXIT_FAILURE);
		}
		return true;
	}
	return false;
}

static bool is_nb_client(const char *flag, const char *arg, server_t **server)
{
	if (!strcmp(flag, FLAG_CLIENT_NB)) {
		if (!nb_client_server(arg, server)) {
			exit(EXIT_FAILURE);
		}
		return true;
	}
	return false;
}

static bool is_freq(const char *flag, const char *arg, server_t **server)
{
	if (!strcmp(flag, FLAG_FREQ)) {
		if (!freq_server(arg, server))
			exit(EXIT_FAILURE);
		return true;
	}
	return false;
}

static bool is_name(const char *flag, const char *arg, server_t **server)
{
	/*if ((*server)->name) {
		free(*server);
		exit(EXIT_FAILURE);
	}*/
	if (!strcmp(flag, SHORT_FLAG_NAME) || !strcmp(flag, LONG_FLAG_NAME)) {
		if (!name_server(arg, server))
			exit(EXIT_FAILURE);
		return true;
	}
	return false;
}

static bool parse_error(const char *flag, const char *arg, server_t **server)
{
	(void)flag;
	(void)arg;
	fprintf(stderr, "%s", HELP_SERVER);
	/*free((*client)->name);
	free(*client);*/
	exit(EXIT_FAILURE);
}

bool parse_arg_server(int argc, char **argv, server_t **server)
{
	if (argc < MIN_ARG_SERVER)
		return fprintf(stderr, "%s\n", HELP_SERVER), false;
	static bool (*arg[4])(const char *, const char *, server_t **);
	arg[0] = is_port;
	arg[1] = is_width;
	arg[2] = is_height;
	arg[3] = is_name;
	arg[4] = is_nb_client;
	arg[5] = is_freq;
	arg[6] = parse_error;
	for (unsigned char y = 1; y + 1 <= argc; y += 2)
		for (unsigned char x = 0;
		     !arg[x](argv[y], argv[y + 1], server); x++);
	return true;
}
