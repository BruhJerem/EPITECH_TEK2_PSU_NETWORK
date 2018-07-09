/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map player
*/

#include <server.h>
#include <stdio.h>
#include "types.h"

ushort_t count_player_in_pos(server_t server, size_t y, size_t x)
{
	player_client_list_t players = server->players;
	player_client_t player = NULL;
	ushort_t count = 0;

	while (players != NULL) {
		player = players->player;
		if (player && player->y == y && player->x == x)
			count++;
		players = players->next;
	}
	return count;
}
