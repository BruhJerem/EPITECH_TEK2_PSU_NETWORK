/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Main client
*/

#include <sys/wait.h>
#include <stdlib.h>
#include "client.h"

int main(int argc, char **argv)
{
	INIT_HOST(client);
	int status;
	if (!parse_arg_client(argc, argv, &client))
		return EXIT_FAILURE;
	if (!fork())
		if (!connect_player(&client))
			return EXIT_FAILURE;
	while ((wait(&status)) > 0);
	return EXIT_SUCCESS;
}
