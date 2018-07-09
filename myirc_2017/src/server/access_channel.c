/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** access_list
*/

#include <stdbool.h>
#include "server.h"
#include <string.h>

channel_t channel_get_elem_at_front(channel_list_t list)
{
	if (list == NULL)
		return 0;
	return list->channel;
}

channel_t channel_get_elem_by_name(channel_list_t list, char *name)
{
	if (!list || !name)
		return NULL;
	if (!strcmp(name, "*"))
		return channel_get_elem_at_front(list);
	while (list) {
		if (!strcmp(name, list->channel->name))
			return list->channel;
		list = list->next;
	}
	return NULL;
}
