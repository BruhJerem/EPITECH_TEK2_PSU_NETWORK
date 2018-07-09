/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** access_list
*/

#include <stdbool.h>
#include <server.h>
#include <string.h>

client_t client_get_elem_at_front(client_list_t list)
{
	if (list == NULL)
		return 0;
	return list->client;
}

client_t client_get_elem_by_nick(client_list_t list, char *name)
{
	if (!list || !name)
		return NULL;
	if (!strcmp(name, "global"))
		return client_get_elem_at_front(list);
	while (list) {
		if (!strcmp(name, list->client->nickname))
			return list->client;
		list = list->next;
	}
	return NULL;
}

client_t client_get_elem_at_position(client_list_t list, unsigned int position)
{
	unsigned int i = 0;

	if (list == NULL)
		return 0;
	if (position == 0)
		return client_get_elem_at_front(list);
	while (i < position) {
		list = list->next;
		if (!list)
			return NULL;
		i++;
	}
	return list->client;
}
