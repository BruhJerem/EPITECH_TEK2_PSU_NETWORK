/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Handle signal
*/

#include <sys/param.h>
#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <stdlib.h>
#include "client.h"

static void *socket_struct_ptr = NULL;

void register_ptr(socket_t socket)
{
	socket_struct_ptr = socket;
}

void sig_handler(int sig)
{
	if (sig == SIGINT) {
		printf("\n%s\n\n", SIGINTSIGNAL);
		destruct_socket(socket_struct_ptr);
		exit(0);
	}
	if (sig == SIGKILL) {
		printf("%s\n", SIGKILLSIGNAL);
		destruct_socket(socket_struct_ptr);
		exit(0);
	}
	if (sig == SIGCHLD) {
		printf("%s\n", SIGKILLSIGNAL);
		destruct_socket(socket_struct_ptr);
		exit(0);
	}
}

bool handle_signal(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if (signal(SIGKILL, sig_handler) == SIG_ERR)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		return fprintf(stderr, "%s\n", strerror(errno)), false;
	return true;
}
