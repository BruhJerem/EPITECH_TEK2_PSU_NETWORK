/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** handle_readable
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"

static bool is_valid_request(client_t client)
{
	if (strlen(client->input) == 2) {
		if (client->input[0] == '\r' && client->input[1] == '\n')
			return false;
	}
	return true;
}

static client_t get_current_client(server_t server, int index)
{
	client_list_t list = server->client_list;
	client_t client = client_get_elem_at_position(list, index);

	return client;
}

static bool concat_str(client_t client, char *c, int rc)
{
	int len;
	int i = 0;

	if (client->input[strlen(client->input)-2] == '\r')
		client->input[strlen(client->input)-2] = '\0';
	if (c[0] != '\n')
		strcat(client->input, c);
	len = rc;
	(void)len;
	while (client->input[i] != '\0' && client->input[i] != '\r') {
		i++;
	}
	if (client->input[i] == '\r') {
		return true;
	}
	return false;
}

static bool get_irc_line(server_t server, int index)
{
	int rc;
	bool close_conn = false;
	char c[1];
	bool reset;
	client_t client = get_current_client(server, index);

	memset(c, 0, 2);
	rc = (int) read(server->fds[index].fd, &c, 1);
	if (rc < 0) {
		perror("read() failed");
		return false;
	}
	if (rc == 0) {
		return handle_disconnect(server, index);
	}
	reset = concat_str(client, c, rc);
	if (reset && is_valid_request(client)) {
		close_conn = parsing(server, client->input, index);
		memset(client->input, 0, READ_SIZE);
	}
	return close_conn;
}

int handle_readable(server_t server, int index)
{
	bool close_conn;

	printf("Descriptor %d is readable\n", server->fds[index].fd);
	close_conn = get_irc_line(server, index);
	check_close_connection(server, close_conn, index);
	return 0;
}
