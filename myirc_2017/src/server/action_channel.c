/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** action_list
*/

#include <stdbool.h>
#include <stdlib.h>
#include <server.h>
#include <string.h>

channel_t create_channel(char *name, enum e_channel_status status)
{
	channel_t channel = malloc(sizeof(struct s_channel));
	client_list_t client_list = malloc(sizeof(struct s_client_list));
	client_t client = malloc(sizeof(struct s_client));
	socket_t socket = malloc(sizeof(struct s_socket));

	if (!channel || !client_list || !client || !socket)
		return NULL;
	strcpy(channel->name, name);
	channel->status = status;
	client->socket = socket;
	client->channel = channel;
	strcpy(client->nickname, "\0");
	client_list->client = client;
	client_list->next = NULL;
	channel->client_list = client_list;
	client->channel = channel;
	return channel;
}

bool channel_add_elem_at_back(channel_list_t front_ptr, channel_t new_element)
{
	channel_list_t new_node = malloc(sizeof(struct s_channel_list));

	new_node->channel = new_element;
	new_node->next = NULL;
	if (new_element == NULL)
		return false;
	if (front_ptr == NULL)
		front_ptr->next = new_node;
	else {
		while (1) {
			if (front_ptr->next == NULL) {
				front_ptr->next = new_node;
				break;
			}
			front_ptr = front_ptr->next;
		}
	}
	return true;
}

void channel_clear(channel_list_t front)
{
	channel_list_t list = front;

	if (!list)
		return;
	channel_clear(list->next);
	free(list);
}
