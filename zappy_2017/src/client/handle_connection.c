/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Handle Connection
*/

#include <time.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include "client.h"

long calc_hash(void)
{
	time_t second = time(NULL);
	pid_t pid;

	if (second == (time_t)-1)
		return fprintf(stderr, "%s\n", strerror(errno)), 0;
	pid = getpid();
	if (!pid)
		return 0;
	return (second * pid);
}

bool connect_player(t_client *client)
{
	if (!create_client_socket(client)) {
		destruct_client_socket(client);
		return false;
	}
	ia_loop(client);
	return true;
}
