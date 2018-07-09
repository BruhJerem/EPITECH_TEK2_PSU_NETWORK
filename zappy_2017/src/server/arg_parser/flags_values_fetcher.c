/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** List of fetcher for the struct arg_t
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "arg_parser.h"

bool get_port(int cnt, int ac, char **av, arg_t data)
{
	(void) ac;
	int res = 0;
	bool ret = true;

	if ((av[cnt + 1] != NULL)) {
		res = advanced_isnum(av[cnt + 1]);
		if (res == -1)
			ret = false;
		else
			data->port = (ushort_t) res;
	}
	else
		ret = false;
	return (ret);
}

bool get_width(int cnt, int ac, char **av, arg_t data)
{
	(void) ac;
	int res = 0;
	bool ret = true;

	if ((av[cnt + 1] != NULL)) {
		res = advanced_isnum(av[cnt + 1]);
		if (res == -1)
			ret = false;
		else
			data->width = (ushort_t) res;
	}
	else
		ret = false;
	return (ret);
}

bool get_height(int cnt, int ac, char **av, arg_t data)
{
	(void) ac;
	int res = 0;
	bool ret = true;
	
	if ((av[cnt + 1] != NULL)) {
		res = advanced_isnum(av[cnt + 1]);
		if (res == -1)
			ret = false;
		else
			data->height = (ushort_t) res;
	}
	else
		ret = false;
	return (ret);
}

bool get_client_nb(int cnt, int ac, char **av, arg_t data)
{
	(void) ac;
	int res = 0;
	bool ret = true;

	if ((av[cnt + 1] != NULL)) {
		res = advanced_isnum(av[cnt + 1]);
		if (res == -1)
			ret = false;
		else
			data->client_nb = (ushort_t) res;
	} else
		ret = false;
	return (ret);
}

bool get_freq(int cnt, int ac, char **av, arg_t data)
{
	(void) ac;
	int res = 0;
	bool ret = true;

	if ((av[cnt + 1] != NULL)) {
		res = advanced_isnum(av[cnt + 1]);
		if (res == -1)
			ret = false;
		else
			data->freq = (ushort_t) res;
	} else
		ret = false;
	if (data->freq < 2 || data->freq > 10000) {
		printf("-f option only accepts integer values between "
				"2 and 10000\n\n");
		ret = false;
	}
	return ret;
}
