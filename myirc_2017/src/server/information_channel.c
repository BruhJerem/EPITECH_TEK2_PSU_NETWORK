/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** information_list
*/

#include <stdbool.h>
#include <stdio.h>
#include <server.h>

void channel_dump(channel_list_t list)
{
	channel_list_t tmp = list;

	while (tmp) {
		printf("%s\n", tmp->channel->name);
		tmp = tmp->next;
	}
}
