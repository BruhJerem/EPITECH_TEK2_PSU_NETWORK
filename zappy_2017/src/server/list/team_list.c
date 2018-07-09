/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Team list management
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

bool add_team(team_list_t list, team_t new_team)
{
	team_list_t new_node = malloc(sizeof(struct s_team));

	if (list == NULL)
		return false;
	if (new_team == NULL)
		return false;
	new_node->team = new_team;
	new_node->next = NULL;
	while (list != NULL) {
		if (list->next == NULL) {
			list->next = new_node;
			return true;
		}
		list = list->next;
	}
	return true;
}

bool delete_team_at_pos(team_list_t *teams, int position)
{
	team_list_t copy = *teams;
	team_list_t next;

	if (*teams == NULL)
		return false;
	if (position == 0) {
		*teams = copy->next;
		free(copy);
		return true;
	}
	for (int i = 0; copy != NULL && i < position - 1; ++i)
		copy = copy->next;
	if (copy == NULL || copy->next == NULL)
		return true;
	next = copy->next->next;
	if (copy->next)
		free(copy->next);
	copy->next = next;
	return true;
}

team_t get_team_by_name(team_list_t list, char *name)
{
	team_t team = NULL;

	if (!name)
		return NULL;
	while (list) {
		team = list->team;
		if (!strcmp(team->name, name))
			return team;
		list = list->next;
	}
	return NULL;
}
