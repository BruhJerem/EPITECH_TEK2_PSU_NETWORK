/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Parse Command
*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include "client.h"

char **parse_look(char *str)
{
	return str_to_wordtab(str, ',');
}

char **parse_inventory(char *str)
{
	return str_to_wordtab(str, ',');
}

int parse_connect_nbr(const char *str)
{
	unsigned int
		connect_nbr = (unsigned int)strtol(str, (char **)NULL, 10);
	printf(SLOT_LEFT, connect_nbr);
	return (connect_nbr) ? (int)connect_nbr :
		fprintf(stderr, "%s\n", strerror(errno)), 0;
}

unsigned int get_nbr_of(t_player **player, int resource)
{
	return (*player)->inventory[resource];
}
