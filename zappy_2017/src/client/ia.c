/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** IA
*/

#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

static bool handle_data(t_client *client, const char *data)
{
	if (!strcmp(data, "WELCOME"))
		return true;
	if (!send_cmd(client, client->name))
		return false;
	return true;
}

void ia_loop(t_client *client)
{
	circular_buffer_t buffer = NULL;
	if (!(buffer = create_circular_buf(DEFAULT_SIZE_READ)))
		destruct_client_socket(client), exit(0);
	while (true) {
		if (!read_answer(client, buffer))
			break;
		if (!handle_data(client, circular_buf_get(buffer)))
			break;
	}
	destruct_client_socket(client);
	exit(0);
}

bool read_answer(t_client *client, circular_buffer_t buffer)
{
	char data[1024];

	if (read(client->fd, &data, BUFFSIZE) - 1) {
		fprintf(stderr, "%s\n", strerror(errno));
		free_circular_buf(buffer);
		return false;
	}
	if (!circular_buf_put(buffer, data))
		return free_circular_buf(buffer), false;
	return true;
}
