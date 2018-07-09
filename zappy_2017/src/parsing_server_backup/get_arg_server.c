/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Get args
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include "server.h"
#include "parse_server.h"

bool port_server(const char *str, server_t server)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]) || x > MAX_SIZE_PORT)
			return fprintf(stderr, "%s\n", ERR_PORT), false;
	}
	(server-> = (int)strtol(str, (char **)NULL, 10));
	if (!(server->port))
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if (((server->port < 1) || server->port > NBR_TOT_PORT))
		return fprintf(stderr, "%s\n", ERR_PORT), false;
	if (server->port <= RESERVED_PORT) {
		return fprintf(stderr, "%s\n", ERR_RESERVED_PORT), false;
	}
	return true;
}

bool width_server(const char *str, server_t **server)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]))
			return fprintf(stderr, "%s\n", ERR_WIDTH), false;
	}
	(*server)->port = (int)strtol(str, (char **)NULL, 10);
	if (!(*server)->port)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if ((*server)->port < 1 || ((*server)->port > MAX_SIZE_MAP))
		return fprintf(stderr, "%s\n", ERR_WIDTH), false;
	return true;
}

bool height_server(const char *str, server_t **server)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]))
			return fprintf(stderr, "%s\n", ERR_HEIGHT), false;
	}
	(*server)->port = (int)strtol(str, (char **)NULL, 10);
	if (!(*server)->port)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if ((*server)->port < 1 || ((*server)->port > MAX_NB_CLIENT))
		return fprintf(stderr, "%s\n", ERR_HEIGHT), false;
	return true;
}

bool nb_client_server(const char *str, server_t **server)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]))
			return fprintf(stderr, "%s\n", ERR_WIDTH), false;
	}
	(*server)->port = (int)strtol(str, (char **)NULL, 10);
	if (!(*server)->port)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if ((*server)->port < 1 || ((*server)->port > ERR_NB_CLIENT))
		return fprintf(stderr, "%s\n", ERR_PORT), false;
	return true;
}

bool freq_server(const char *str, server_t server)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]))
			return fprintf(stderr, "%s\n", ERR_FREQ), false;
	}

	server-> = (int)strtol(str, (char **)NULL, 10);
	if (!(*server)->port)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if ((*server)->port < MIN_FREQ || ((*server)->port > MAX_FREQ))
		return fprintf(stderr, "%s\n", ERR_FREQ), false;
	return true;
}

bool name_server(const char *str, server_t **server)
{
	for (unsigned int x = 0; str[x]; x++)
		if (!isalnum(str[x]))
			return fprintf(stderr, "%s\n", ERR_NAME), false;
	(*server)->name = strdup(str);
	return true;
}
