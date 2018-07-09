/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server debug functions
*/

#include <stdio.h>
#include "server.h"

static void debug_player_inventory(player_client_t player)
{
	inventory_t inventory = player->inventory;

	printf("\t\tfood : %d\n", inventory->food);
	printf("\t\tlinemate : %d\n", inventory->linemate);
	printf("\t\tderaumere : %d\n", inventory->deraumere);
	printf("\t\tsibur : %d\n", inventory->sibur);
	printf("\t\tmendiane : %d\n", inventory->mendiane);
	printf("\t\tphiras : %d\n", inventory->phiras);
	printf("\t\tthystame : %d\n", inventory->thystame);
}

static void debug_players(player_client_list_t list)
{
	player_client_t player;

	if (list == NULL)
		return;
	while (list) {
		player = list->player;
		if (!player || player->state == AWAITING_TEAM_NAME)
			continue;
		printf("player id <%d>", player->id);
		printf("with fd <%d> :\n", player->socket->fd);
		printf("\tteam name : %s\n", player->team_name);
		printf("\tlevel : %d\n", player->level);
		printf("\tinventory :\n");
		debug_player_inventory(player);
		list = list->next;
	}
}

static void debug_team_list(team_list_t teams)
{
	team_list_t list_copy = teams;

	while (list_copy != NULL) {
		printf("> %s\n", list_copy->team->name);
		list_copy = list_copy->next;
	}
}

void debug_server(server_t server)
{
	player_client_list_t client_list = server->players;
	team_list_t team_list = server->teams;

	printf("--------> Players connected <--------\n");
	debug_players(client_list);
	printf("--------------> Teams <--------------\n");
	debug_team_list(team_list);
	printf("-------------------------------------\n");
}
