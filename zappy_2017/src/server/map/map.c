/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "server.h"

map_t init_map(size_t height, size_t width)
{
	map_t new_map = malloc(sizeof(struct s_map));
	size_t max_map_size = height * width;

	if (!new_map)
		return NULL;
	new_map->tiles = malloc(sizeof(struct s_tile) * (max_map_size));
	if (!new_map->tiles)
		return NULL;
	new_map->height = height;
	new_map->width = width;
	new_map->nbr_item = 0;
	for (size_t i = 0; i <= max_map_size - 1; i++) {
		new_map->tiles[i] = malloc(sizeof(struct s_tile));
		if (!new_map->tiles[i])
			return NULL;
		new_map->tiles[i]->y = i / width;
		new_map->tiles[i]->x = i - (new_map->tiles[i]->y * width);
		new_map->tiles[i]->inventory = NULL;
	}
	return new_map;
}

void debug_map(map_t map)
{
	size_t max_map_size = map->height * map->width;
	tile_t tile = NULL;

	for (size_t i = 0; i <= max_map_size - 1; i++) {
		tile = map->tiles[i];
		printf("tiles[%lu] :\n", i);
		printf("\tptr : %p\n", (void *) tile);
		printf("\tpos : %lu-%lu\n", tile->y, tile->x);
		printf("\tinventory :\n");
		printf("\t\tfood : %d\n", tile->inventory->food);
		printf("\t\tlinemate : %d\n", tile->inventory->linemate);
		printf("\t\tderaumere : %d\n", tile->inventory->deraumere);
		printf("\t\tsibur : %d\n", tile->inventory->sibur);
		printf("\t\tmendiane : %d\n", tile->inventory->mendiane);
		printf("\t\tphiras : %d\n", tile->inventory->phiras);
		printf("\t\tthystame : %d\n", tile->inventory->thystame);
	}
	printf("total nbr of items : %lu\n", map->nbr_item);
}

void free_map(map_t map)
{
	size_t max_map_size = map->height * map->width;

	for (size_t i = 0; i <= max_map_size - 1; i++) {
		if (map->tiles[i]->inventory)
			free(map->tiles[i]->inventory);
		if (map->tiles[i])
			free(map->tiles[i]);
	}
	if (map->tiles)
		free(map->tiles);
	map->tiles = NULL;
}

int get_tile_index(map_t map, int y, int x)
{
	int index = 0;
	int mod_y = y % (int) map->height;
	int mod_x = x % (int) map->width;

	if (mod_y < 0)
		mod_y += map->height;
	if (mod_x < 0)
		mod_x += map->width;
	index = (mod_y * (int) map->width) + mod_x;
	if (index >= ((int) map->height * (int) map->width) || index < 0)
		return -1;
	return index;
}
