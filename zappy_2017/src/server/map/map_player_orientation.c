/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map player orientation
*/

#include "server.h"

void forward_player(map_t map, player_client_t player)
{
	if (player->orientation == NORTH) {
		if (player->y == 0)
			player->y = map->height - 1;
		else
			player->y--;
	} else if (player->orientation == SOUTH) {
		if (player->y + 1 == map->height - 1)
			player->y = 0;
		else
			player->y++;
	} else if (player->orientation == EAST) {
		if (player->x + 1 == map->width - 1)
			player->x = 0;
		else
			player->x++;
	} else if (player->orientation == WEST) {
		if (player->x == 0)
			player->x = map->width - 1;
		else
			player->x--;
	}
}

void left_player(player_client_t player)
{
	if (player->orientation == NORTH)
		player->orientation = WEST;
	else if (player_orientation == SOUTH)
		player->orientation = EAST;
	else if (player->orientation == EAST)
		player->orientation = NORTH;
	else if (player->orientation == WEST)
		player->orientation = SOUTH;
}

void right_player(player_client_t player)
{
	if (player->orientation == NORTH)
		player->orientation = EAST;
	else if (player_orientation == SOUTH)
		player->orientation = WEST;
	else if (player->orientation == EAST)
		player->orientation = SOUTH;
	else if (player->orientation == WEST)
		player->orientation = NORTH;
}
