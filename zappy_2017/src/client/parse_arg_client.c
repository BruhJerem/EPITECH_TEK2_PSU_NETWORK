/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Parse args
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

static bool is_port(const char *flag, const char *arg, t_client *client)
{
	if (!strcmp(flag, SHORT_FLAG_PORT) || !strcmp(flag, LONG_FLAG_PORT)) {
		if (!port_client(arg, client))
			exit(EXIT_FAILURE);
		return true;
	}
	return false;
}

static bool is_name(const char *flag, const char *arg, t_client *client)
{
	if (!strcmp(flag, SHORT_FLAG_NAME) || !strcmp(flag, LONG_FLAG_NAME)) {
		if (!name_client(arg, client))
			exit(EXIT_FAILURE);
		return true;
	}
	return false;
}

static bool is_host(const char *flag, const char *arg, t_client *client)
{
	if (!strcmp(flag, SHORT_FLAG_HOST) || !strcmp(flag, LONG_FLAG_HOST)) {
		if (!host_client(arg, client))
			exit(EXIT_FAILURE);
		return true;
	}
	return false;
}

static bool parse_error(const char *flag, const char *arg, t_client *client)
{
	(void)flag;
	(void)arg;
	fprintf(stderr, "%s", HELP);
	free(client->name);
	free(client);
	exit(EXIT_FAILURE);
}

bool parse_arg_client(int argc, char **argv, t_client *client)
{
	if (!(argc % 2) || argc < 5 || argc > 7)
		return fprintf(stderr, "%s\n", HELP), false;
	static bool (*arg[4])(const char *, const char *, t_client *);
	arg[0] = is_port;
	arg[1] = is_name;
	arg[2] = is_host;
	arg[3] = parse_error;
	for (unsigned char y = 1; y + 1 <= argc; y += 2)
		for (unsigned char x = 0;
			!arg[x](argv[y], argv[y + 1], client); x++);
	if (!client->machine)
		client->machine = LOCALHOST;
	return true;
}
