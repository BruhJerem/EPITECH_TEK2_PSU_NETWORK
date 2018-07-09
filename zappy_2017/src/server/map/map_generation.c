/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Map generation functions
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "server.h"

static ushort_t gen_ressource(map_t map, size_t intensity_gen)
{
	ushort_t nbr = (ushort_t) (rand() % intensity_gen);

	map->nbr_item += nbr;
	return nbr;
}

bool generate_map(map_t map)
{
	size_t max_map_size = map->height * map->width;
	time_t t;

	srand((unsigned int) time(&t));
	for (size_t i = 0; i <= max_map_size - 1; i++) {
		map->tiles[i]->inventory = malloc(sizeof(struct s_inventory));
		if (!map->tiles[i]->inventory)
			return false;
		map->tiles[i]->inventory->food = gen_ressource(map, 3);
		map->tiles[i]->inventory->linemate = gen_ressource(map, 2);
		map->tiles[i]->inventory->deraumere = gen_ressource(map, 2);
		map->tiles[i]->inventory->sibur = gen_ressource(map, 2);
		map->tiles[i]->inventory->mendiane = gen_ressource(map, 2);
		map->tiles[i]->inventory->phiras = gen_ressource(map, 2);
		map->tiles[i]->inventory->thystame = gen_ressource(map, 2);
	}
	return true;
}
