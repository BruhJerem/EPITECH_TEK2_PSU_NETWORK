/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Main client
*/

#include <stdio.h>
#include <stdlib.h>
#include <parse_server.h>

int main(int argc, char **argv)
{
	t_client *server = NULL;
	/*if (!(client = malloc(sizeof(t_client))))
		return fprintf(stderr, "%s\n", strerror(errno)),
	 EXIT_FAILURE;*/
	if (!parse_arg_server(argc, argv, &server))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
