/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** init_server
*/

#include <stdbool.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <string.h>
#include <poll.h>
#include "common.h"
#include "server.h"

static channel_t init_create_channel(char *name, enum e_channel_status status)
{
	channel_t channel = malloc(sizeof(struct s_channel));
	client_list_t client_list = malloc(sizeof(struct s_client_list));
	client_t cl_tmp = malloc(sizeof(struct s_client));
	socket_t socket = malloc(sizeof(struct s_socket));

	if (!channel || !client_list || !cl_tmp || !socket)
		return NULL;
	strcpy(channel->name, name);
	channel->status = status;
	cl_tmp->channel = channel;
	cl_tmp->socket = socket;
	client_list->client = cl_tmp;
	client_list->next = NULL;
	channel->client_list = client_list;
	return channel;
}

static channel_list_t init_channel_list(void)
{
	channel_list_t list = malloc(sizeof(struct s_channel_list));

	if (!list)
		return NULL;
	list->channel = init_create_channel("*", PUBLIC);
	list->next = NULL;
	return list;
}

static client_list_t init_client_list(int fd, channel_t channel)
{
	client_list_t client_list = malloc(sizeof(struct s_client_list));
	client_t client = malloc(sizeof(struct s_client));
	socket_t socket = malloc(sizeof(struct s_socket));

	if (!client_list || !client || !socket)
		return NULL;
	client->channel = channel;
	client->status = LOGOUT;
	strcpy(client->username, "NickServ");
	strcpy(client->nickname, "NickServ");
	memset(client->input, 0, READ_SIZE);
	client->socket = socket;
	client->socket->fd = fd;
	client_list->client = client;
	client_list->next = NULL;
	return client_list;
}

/**
* Initialize the pollfd structure
* Set up the initial listening socket
*/

server_t init_server(char **argv)
{
	server_t server = malloc(sizeof(struct s_server));
	unsigned short port = (unsigned short) strtoul(argv[1], NULL, 0);

	if (!server)
		return NULL;
	server->socket = create_socket(INADDR_ANY, port);
	server->socket->ip = "localhost";
	memset(server->fds, 0, sizeof(server->fds));
	server->fds[0].fd = server->socket->fd;
	server->fds[0].events = POLLIN;
	server->size_client = 0;
	server->end_server = false;
	server->compress_fd = false;
	server->channel_list = init_channel_list();
	server->client_list = init_client_list(server->socket->fd,
			channel_get_elem_at_front(server->channel_list));
	server->channel_list->channel->client_list->client =
		server->client_list->client;
	set_bind(server->socket);
	set_listen(server->socket);
	return server;
}
