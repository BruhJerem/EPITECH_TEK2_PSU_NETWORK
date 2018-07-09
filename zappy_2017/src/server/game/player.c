/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player functions
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

player_client_t create_player_client(server_t server, socket_t socket,
				     nfds_t poll_index)
{
	player_client_t	player_client = malloc(sizeof(struct s_player_client));
	inventory_t inventory = create_inventory();

	if (!player_client || !socket || !inventory)
		return NULL;
	player_client->poll_idx = poll_index;
	player_client->socket = socket;
	player_client->id = server->nbr_player;
	server->nbr_player++;
	player_client->inventory = inventory;
	player_client->team_name = NULL;
	player_client->state = AWAITING_TEAM_NAME;
	player_client->level = 1;
	memset(player_client->buffer, 0, READ_SIZE);
	return player_client;
}
