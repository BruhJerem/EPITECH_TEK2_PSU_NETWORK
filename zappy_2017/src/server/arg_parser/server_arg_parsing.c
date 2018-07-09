/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Arg parser for the server
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arg_parser.h"

/*
** Will check all the arg and return an error message
** if needed
*/
const char *flags_tab[6] = {"-p", "-x", "-y", "-n", "-c", "-f"};

static bool (*values_analyzer[6])(int cnt, int ac, char **av, arg_t data) =
{
	&get_port,
	&get_width,
	&get_height,
	&get_team_name,
	&get_client_nb,
	&get_freq
};

static bool fill_data_struct(int ac,char **av, arg_t data)
{
	bool ret = true;

	for (int cnt = 0; (cnt < (ac - 1) && ret != false); cnt++) {
		for (int x = 0; x < 6; x++) {
			if (strcmp(flags_tab[x], av[cnt]) == 0)
				ret = values_analyzer[x](cnt, ac, av, data);
		}
	}
	return ret;
}

bool parser_launcher(int ac, char **av, arg_t data)
{
	init_struct(data);
	if (ac < 2)
		return (true);
	if ((strcmp(av[1], "-h") == 0) || (strcmp(av[1], "--help") == 0)) {
		display_help();
		return false;
	}
	if (fill_data_struct(ac, av, data) == false) {
		printf("%s", ARG_INVALID_ARG_ERROR);
		return false;
	}
	return true;
}
