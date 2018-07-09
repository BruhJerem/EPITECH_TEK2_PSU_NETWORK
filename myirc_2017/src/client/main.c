/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Client main file
*/

#include <unistd.h>
#include "client.h"

int main(int ac, char **av)
{
	client_t client;

	(void) av;
	if (ac != 1)
		return 84;
	client = init_client();
	if (client == NULL)
		return 84;
	client_loop(client);
	return 0;
}
