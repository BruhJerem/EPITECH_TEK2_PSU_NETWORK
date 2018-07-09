/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map player vision
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib-tools.h"
#include "server.h"

static void print_tile_ressource(char **inv, const char *ressource, ushort_t nb)
{
	size_t old_size = 0;
	size_t new_size = 0;

	if (!inv || *inv == NULL)
		return;
	if (!ressource || strlen(ressource) == 0 || nb == 0)
		return;
	old_size = strlen(*inv);
	new_size = ((strlen(ressource) + 1) * nb) + 1;
	*inv = realloc(*inv, sizeof(char) * (old_size + new_size));
	for (ushort_t i = 1; i <= nb; i++) {
		strcat(*inv, ressource);
		strcat(*inv, " \0");
	}
}

static void look_at_tile(server_t server, char **inv, int tile_index)
{
	inventory_t inventory = server->map->tiles[tile_index]->inventory;
	tile_t tile = server->map->tiles[tile_index];
	ushort_t player_in_tile = count_player_in_pos(server, tile->y, tile->x);

	if (player_in_tile != 0)
		print_tile_ressource(inv, "player", player_in_tile);
	if (inventory->food != 0)
		print_tile_ressource(inv, "food", inventory->food);
	if (inventory->linemate != 0)
		print_tile_ressource(inv, "linemate", inventory->linemate);
	if (inventory->deraumere != 0)
		print_tile_ressource(inv, "deraumere", inventory->deraumere);
	if (inventory->sibur != 0)
		print_tile_ressource(inv, "sibur", inventory->sibur);
	if (inventory->mendiane != 0)
		print_tile_ressource(inv, "mendiane", inventory->mendiane);
	if (inventory->phiras != 0)
		print_tile_ressource(inv, "phiras", inventory->phiras);
	if (inventory->thystame != 0)
		print_tile_ressource(inv, "thystame", inventory->thystame);
}

static void get_look_orientation(look_t *infos, player_client_t player,
				ushort_t i_level)
{
	if (player->orientation == NORTH) {
		infos->x = (int) player->x - i_level;
		infos->y = (int) player->y - i_level;
		infos->start = infos->x;
		infos->end = infos->start + (i_level * 2) + 1;
	} else if (player->orientation == SOUTH) {
		infos->x = (int) player->x + i_level;
		infos->y = (int) player->y + i_level;
		infos->start = infos->x;
		infos->end = infos->start - (i_level * 2) - 1;
	} else if (player->orientation == EAST) {
		infos->x = (int) player->x + i_level;
		infos->y = (int) player->y - i_level;
		infos->start = infos->y;
		infos->end = infos->start + (i_level * 2) + 1;
	} else if (player->orientation == WEST)
		infos->x = (int) player->x - i_level,
		infos->y = (int) player->y + i_level,
		infos->start = infos->y,
		infos->end = infos->start - (i_level * 2) - 1;
}

static void look_at_multiple_tiles(server_t server, char **inv,
				player_client_t player, ushort_t i_level)
{
	int idx = 0;

	INIT_LOOK(infos);
	get_look_orientation(&infos, player, i_level);

	printf("Start : %d\n", infos.start);
	printf("End : %d\n", infos.end);

	while (infos.start != infos.end) {
		*inv = realloc(*inv, strlen(*inv) + 2);
		ov_strcat(*inv, ", ", 1);
		if (player->orientation == NORTH) {
			idx = get_tile_index(server->map, infos.y, infos.start);
			infos.start++;
		} else if (player->orientation == SOUTH) {
			idx = get_tile_index(server->map, infos.y, infos.start);
			infos.start--;
		} else if (player->orientation == EAST) {
			idx = get_tile_index(server->map, infos.start, infos.x);
			infos.start++;
		} else if (player->orientation == WEST) {
			idx = get_tile_index(server->map, infos.start, infos.x);
			infos.start--;
		}
		look_at_tile(server, inv, idx);
	}
}

void player_look_tiles(server_t server, player_client_t player)
{
	char *inv = malloc(sizeof(char) * 2);
	int tile_index = 0;

	printf("Player :\n");
	printf("\tlevel : %d\n", player->level);
	printf("\torientation : %d\n", player->orientation);
	printf("\ty : %lu\n", player->y);
	printf("\tx : %lu\n", player->x);

	strcpy(inv, "[");
	for (ushort_t i = 0; i <= player->level; i++) {
		if (i == 0) {
			tile_index = get_tile_index(server->map,
				(int) player->y, (int) player->x);
			look_at_tile(server, &inv, tile_index);
		} else
			look_at_multiple_tiles(server, &inv, player, i);
		printf("INV AT %d :\n\t|%s|\n", i, inv);
	}
	inv[strlen(inv) - 1] = ']';
	printf("INV FINAL :\n\t|%s|\n", inv);
	if (inv)
		free(inv);
}
