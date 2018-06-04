/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** server
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#include <zconf.h>
#include <string.h>
#include <printf.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <wait.h>
#include "server.h"
#include "lib/get_next_line.h"

static const server_t *g_server = NULL;

static bool message_connection(server_t *serv)
{
	if (write(serv->client_fd, "220 (vsFTPd 3.0.0)\n",
	strlen("220 (vsFTPd 3.0.0)\n")) < 0)
		return false;
	return true;
}

/**
* Connection and forking server
* @param serv
* @return
*/

int handle_accept(server_t *serv)
{
	serv = accept_server(serv);
	if (!serv || !message_connection(serv))
		return 84;
	printf("Connection from %s\n", inet_ntoa(serv->s_in_client.sin_addr));
	if (fork() == 0) {
		if (!read_from_client(serv))
			exit(84);
		exit(0);
	}
	if (close(serv->client_fd) == -1)
		return 84;
	return 0;
}

/**
* Initialization of the server structure
* @param port
* @param av
* @return
*/

static server_t *init_struct(unsigned short port, char **av)
{
	server_t *serv = malloc(sizeof(server_t));
	connection_t *connection = malloc(sizeof(connection_t));
	path_t *path = malloc(sizeof(path_t));
	struct protoent *pe = getprotobyname("TCP");

	if (!serv || !connection || !pe || !path)
		return NULL;
	serv->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (serv->fd == -1)
		return NULL;
	serv->port = port;
	serv->path = path;
	find_home_path(serv, av[2]);
	serv->path->curr = strdup(serv->path->home);
	serv->connection = connection;
	serv->connection->is_connected = EMPTY;
	serv->connection->usename_cmd = NULL;
	serv->connection->password_cmd = NULL;
	serv->data_mode = NONE;
	return serv;
}

/**
* Signal handler
* @param sig
*/

static void sighandler(int sig)
{
	(void)sig;
	quit_function((server_t *) g_server, NULL);
	dprintf(g_server->fd, "Server shutdown...\n");
	close(g_server->fd);
	exit(0);
}

/**
* MAIN LOOP : get signal and handle server
* @param av
* @return
*/

int server(char **av)
{
	server_t *serv = init_struct((unsigned short) strtoul(av[1], NULL, 0),
				av);

	if (chdir(av[2]) == -1) {
		printf("ERROR: Directory do not exist.\n");
		return 84;
	}
	if (!serv || !start_server(serv))
		return 84;
	while (true) {
		g_server = serv;
		signal(SIGINT, sighandler);
		signal(SIGPIPE, sighandler);
		if (handle_accept(serv) == 84) {
			if (close(serv->fd) == -1)
				return 84;
			return 84;
		}
	}
}