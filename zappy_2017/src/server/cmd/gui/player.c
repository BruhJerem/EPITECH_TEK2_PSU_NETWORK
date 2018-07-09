/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player ui cmd function
*/

#include <stdio.h>
#include <stdlib.h>
#include "lib-tools.h"
#include "server.h"

bool ppo(server_t server, char **cmd, int index)
{
	player_client_list_t players = server->players;
	player_client_t player;
	size_t player_id = 0;

	if (tab_len(cmd) < 2 || cmd[1][0] != '#' || !str_is_number(&cmd[1][1])) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	player_id = (size_t) atoi(&cmd[1][1]);
	player = get_player_by_id(players, player_id);
	if (!player) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	dprintf(server->poll_fds[index].fd, C_PPO, player->id,
		player->x, player->y, player->orientation);
	return true;
}

bool plv(server_t server, char **cmd, int index)
{
	player_client_list_t players = server->players;
	player_client_t player_client;
	size_t player_id = 0;

	if (tab_len(cmd) < 2 || cmd[1][0] != '#' || !str_is_number(&cmd[1][1])) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	player_id = (size_t) atoi(&cmd[1][1]);
	player_client = get_player_by_id(players, player_id);
	if (!player_client) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	dprintf(server->poll_fds[index].fd, C_PLV, player_client->id,
		player_client->level);
	return true;
}

bool pin(server_t server, char **cmd, int index)
{
	player_client_list_t players = server->players;
	player_client_t player;
	size_t player_id = 0;

	if (tab_len(cmd) < 2 || cmd[1][0] != '#' || !str_is_number(&cmd[1][1])) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	player_id = (size_t) atoi(&cmd[1][1]);
	player = get_player_by_id(players, player_id);
	if (!player) {
		dprintf(server->poll_fds[index].fd, "ko\n");
		return false;
	}
	send_player_inventory(player, server->poll_fds[index].fd);
	return true;
}
