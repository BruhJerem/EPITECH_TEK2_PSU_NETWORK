/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Socket functions
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "common.h"

bool connect_socket(socket_t socket)
{
	struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons((uint16_t) socket->port);
	sin.sin_addr.s_addr = inet_addr(socket->ip);
	if (connect(socket->fd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		if (close(socket->fd) == -1)
			return false;
		return false;
	}
	return true;
}
