/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Server main file
*/

#include <stdlib.h>
#include "server.h"
#include "arg_parser.h"

/*Struct serv map team list et team*/
/*Remplire listes chainées*/
/*Initialiser port socket s_server*/

int main(int ac, char **av)
{
	server_t server;
	arg_t args = malloc(sizeof(struct s_arg));

	if (!args || !parser_launcher(ac, av, args))
		return 84;
	server = init_server(args);
	if (!server)
		return 84;
	if (!server_loop(server))
		return 84;
	return 0;
}
