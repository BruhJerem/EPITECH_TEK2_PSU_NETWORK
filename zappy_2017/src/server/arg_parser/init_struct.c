/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init_struct
*/

#include <string.h>
#include <stdlib.h>
#include "arg_parser.h"

void init_struct(arg_t data)
{
	data->team_name = malloc(sizeof(char *) * 3);
	data->client_nb = 5;
	data->width = 10;
	data->height = 10;
	data->port = 4242;
	data->freq = 2;
	data->team_name[0] = strdup("team1");
	data->team_name[1] = strdup("team2");
	data->team_name[2] = NULL;
}
