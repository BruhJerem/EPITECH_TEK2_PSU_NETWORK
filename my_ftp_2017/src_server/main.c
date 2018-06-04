/*
** EPITECH PROJECT, 2018
** Project
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

/**
* Print the usage
* @param exe
* @param ret_value
* @return
*/

static int usage(char *exe, int ret_value)
{
	printf("USAGE: %s port path\n\t", exe);
	printf("port is the port number on which the server socket listens\n");
	printf("\tpath is the path to the home directory for "
		"the Anonymous user\n");
	return ret_value;
}

/**
* Main function
* @param ac
* @param av
* @return
*/

int main(int ac, char **av)
{
	if (ac == 2) {
		if (!strcmp(av[1], "-help"))
			return usage(av[0], 0);
		return usage(av[0], 84);
	}
	if (ac != 3)
		return usage(av[0], 84);
	return server(av);
}