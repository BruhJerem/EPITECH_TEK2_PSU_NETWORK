/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player events (send to UI)
*/

#include <stdio.h>
#include "server.h"

void player_connect_event(server_t server, player_client_t player)
{
	gen_player_information(server->map, player);
	player_look_tiles(server, player); // DEBUG - A RETIRER PLUS TARD
	if (server->ui) {
		dprintf(server->ui->socket->fd, C_PNW, player->id,
			player->x, player->y, player->orientation,
			player->level, player->team_name
		);
		dprintf(server->ui->socket->fd, C_PLV,
			player->id, player->level
		);
	}
	player->state = ONLINE;
}

void player_disconnect_event(server_t server, player_client_t player)
{
	if (server->ui) {
		dprintf(server->ui->socket->fd, C_PDI, player->id);
	}
}

void player_move_event(server_t server, player_client_t player)
{
	if (server->ui) {
		dprintf(server->ui->socket->fd, C_PPO, player->id,
			player->x, player->y, player->orientation
		);
	}
}
