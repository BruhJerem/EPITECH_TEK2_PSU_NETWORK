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
#include "client.h"

bool port_client(const char *str, t_client *client)
{
	for (int x = 0; str[x]; x++) {
		if (!isdigit(str[x]) || x > MAX_SIZE_PORT)
			return fprintf(stderr, "%s\n", ERR_PORT), false;
	}
	client->port = (int)strtol(str, (char **)NULL, 10);
	if (!client->port)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if (((client)->port < 1) || (client->port > NBR_TOT_PORT))
		return fprintf(stderr, "%s\n", ERR_PORT), false;
	if (client->port <= RESERVED_PORT)
		return fprintf(stderr, "%s\n", ERR_RESERVED_PORT), false;
	return true;
}

bool name_client(const char *str, t_client *client)
{
	for (unsigned int x = 0; str[x]; x++)
		if (!isalnum(str[x]))
			return fprintf(stderr, "%s\n", ERR_NAME), false;
	client->name = strdup(str);
	return true;
}

bool host_client(const char *str, t_client *client)
{
	for (unsigned int x = 0; str[++x]; x++)
		if (!isdigit(str[x]) && str[x] != 46)
			return fprintf(stderr, "%s\n", ERR_HOST), false;
	client->machine = strdup(str);
	return true;
}
