/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Player list management
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

bool add_player(player_client_list_t *list, player_client_t new_player)
{
	player_client_list_t new_node;

	new_node = malloc(sizeof(struct s_player_client_list));
	if (!new_node)
		return false;
	new_node->player = new_player;
	new_node->next = (*list);
	(*list) = new_node;
	return true;
}

bool delete_player_by_fd(player_client_list_t *list, int fd)
{
	player_client_list_t *list_copy = list;
	player_client_list_t current;

	while (*list_copy != NULL) {
		current = *list_copy;
		if (current->player->socket->fd == fd) {
			*list_copy = current->next;
			free(current);
			break;
		}
		list_copy = &(current->next);
	}
	return true;
}

player_client_t get_player_by_fd(player_client_list_t list, int fd)
{
	player_client_list_t list_copy = list;

	while (list_copy != NULL) {
		if (list_copy->player->socket->fd == fd)
			return list_copy->player;
		list_copy = list_copy->next;
	}
	return NULL;
}

player_client_t get_player_by_id(player_client_list_t list, size_t id)
{
	player_client_t client;

	if (list == NULL)
		return NULL;
	while (list) {
		client = list->player;
		if (!client)
			continue;
		if (client->id == id)
			return client;
		list = list->next;
	}
	return NULL;
}
