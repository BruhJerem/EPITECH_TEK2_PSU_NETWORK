/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Server main file
*/

#include <stdio.h>
#include <server.h>
#include <string.h>
#include <stdlib.h>

int usage(int return_value, char *exe)
{
	printf("USAGE: %s port\n", exe);
	return return_value;
}

void free_struct(server_t server)
{
	client_clear(server->client_list);
	free(server);
}

int main(int ac, char **av)
{
	server_t server;

	if (ac != 2)
		return usage(84, av[0]);
	if (!strcmp("-help", av[1]))
		return usage(0, av[0]);
	server = init_server(av);
	if (!server)
		return 84;
	start_process(server);
	free_struct(server);
	return 0;
}
