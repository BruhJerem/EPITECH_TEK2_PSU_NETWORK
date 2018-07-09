/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** information_list
*/

#include <stdbool.h>
#include <stdio.h>
#include <server.h>
#include <stdlib.h>

void client_dump(client_list_t list)
{
	client_list_t tmp = list;

	while (tmp) {
		printf("%s : ", tmp->client->username);
		printf("%s\n", tmp->client->nickname);
		tmp = tmp->next;
	}
}

void client_clear(client_list_t front)
{
	client_list_t list = front;

	if (!list)
		return;
	client_clear(list->next);
	free(list);
}
