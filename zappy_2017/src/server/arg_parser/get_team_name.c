/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Flags fetcher list
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "arg_parser.h"

int advanced_isnum(char *str)
{
	int i;
	int ret;

	for (i = 0; str[i]; i++) {
		if ((str[i] < '0') || (str[i] > '9'))
			ret = -1;
	}
	ret = atoi(str);
	return ret;
}

bool check_flags_pos(int cnt, char **av)
{
	int x = 0;
	bool verif = true;

	if (av[cnt + 1] != NULL)
		cnt++;
	if (av[cnt + 1] != NULL)
		for (x = 0; x < 6; x++) {
			if (strcmp(av[cnt], flags_tab[x]) == 0)
				verif = false;
		}
	return (verif);
}

char **set_tab_name(int ac)
{
	char **tab;

	tab = malloc(sizeof(char *) * (ac + 1));
	if (!tab)
		return NULL;
	for (int i = 0; i < ac; i++) {
		tab[i] = malloc(sizeof(char));
		if (!tab[i])
			return NULL;
	}
	return (tab);
}

bool get_team_name(int cnt, int ac, char **av, arg_t data)
{
	int x = 0;
	bool ret = true;

	data->team_name = set_tab_name(ac);
	if (av[cnt + 1] && check_flags_pos(cnt, av) == true) {
		for (x = 0; check_flags_pos(cnt, av) == true; x++) {
			data->team_name[x] = av[cnt + 1];
			cnt++;
		}
		data->team_name[x] = NULL;
	} else {
		ret = false;
	}
	return (ret);
}
