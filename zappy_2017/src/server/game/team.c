/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Team management
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

team_t create_team(char *name)
{
	team_t team = malloc(sizeof(struct s_team));

	if (!team)
		return NULL;
	team->name = strdup(name);
	team->nbr_player = 0;
	return team;
}

team_list_t init_team_list(char **teams_name)
{
	team_list_t teams = malloc(sizeof(struct s_team_list));
	team_t team = NULL;

	teams->team = create_team(teams_name[0]);
	teams->next = NULL;
	for (int i = 1; teams_name[i] != NULL ; i++) {
		team = create_team(teams_name[i]);
		add_team(teams, team);
	}
	return teams;
}

void send_teams(server_t server, int fd)
{
	team_list_t team_list = server->teams;
	team_t team = NULL;

	while (team_list) {
		team = team_list->team;
		if (team && team->name)
			dprintf(fd, C_TNA, team->name);
		team_list = team_list->next;
	}
}
