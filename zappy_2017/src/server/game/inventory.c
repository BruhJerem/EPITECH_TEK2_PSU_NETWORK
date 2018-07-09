/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Inventory functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

inventory_t create_inventory(void)
{
	inventory_t inventory = malloc(sizeof(struct s_inventory));

	if (!inventory)
		return NULL;
	inventory->food = 0;
	inventory->linemate = 0;
	inventory->deraumere = 0;
	inventory->sibur = 0;
	inventory->mendiane = 0;
	inventory->phiras = 0;
	inventory->thystame = 0;
	return inventory;
}

void send_tile_inventory(tile_t tile, int fd)
{
	dprintf(fd, C_BCT, tile->y, tile->x, tile->inventory->food,
		tile->inventory->linemate, tile->inventory->deraumere,
		tile->inventory->sibur, tile->inventory->mendiane,
		tile->inventory->phiras, tile->inventory->thystame
	);
}

void send_tiles_inventory(server_t server, int fd)
{
	map_t map = server->map;
	size_t max_map_size = (map->width * map->height) - 1;

	for (size_t idx = 0; idx <= max_map_size; idx++) {
		send_tile_inventory(map->tiles[idx], fd);
	}
}

void send_player_inventory(player_client_t player, int fd)
{
	inventory_t inventory = player->inventory;

	dprintf(fd, C_PIN, player->id, player->x, player->y, inventory->food,
		inventory->linemate, inventory->deraumere, inventory->sibur,
		inventory->mendiane, inventory->phiras, inventory->thystame
	);
}
