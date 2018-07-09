/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map player generation
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void gen_player_information(map_t map, player_client_t player_client)
{
	size_t max_x = map->width - 1;
	size_t max_y = map->height - 1;
	int orientation = (rand() % 4) + 1;

	player_client->y = rand() % max_y;
	player_client->x = rand() % max_x;
	player_client->orientation = (enum e_player_orientation) orientation;
	/* DEBUG
	printf("map infos :\n");
	printf("\tmax_y : %lu\n", max_y);
	printf("\tmax_x : %lu\n", max_x);
	printf("player infos :\n");
	printf("\ty : %lu\n", player_client->y);
	printf("\tx : %lu\n", player_client->x);
	printf("\to : %d\n", (int) player_client->orientation);

	if (player_client->orientation == NORTH)
		printf("\torientation : NORTH\n");
	else if (player_client->orientation == SOUTH)
		printf("\torientation : SOUTH\n");
	else if (player_client->orientation == EAST)
		printf("\torientation : EAST\n");
	else if (player_client->orientation == WEST)
		printf("\torientation : WEST\n");
	else
		printf("\torientation : N/A\n");
	*/
}
