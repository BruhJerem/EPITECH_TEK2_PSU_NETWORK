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

client_t create_client(int fd, char *name)
{
	client_t client = malloc(sizeof(struct s_client));
	channel_t channel = malloc(sizeof(struct s_channel));
	socket_t socket = malloc(sizeof(struct s_socket));
	client_list_t list = malloc(sizeof(struct s_client_list));

	if (!client || !channel || !socket || !list)
		return NULL;
	strcpy(client->nickname, name);
	strcpy(client->username, name);
	client->status = LOGOUT;
	channel->client_list = list;
	channel->client_list->next = NULL;
	memset(client->input, 0, READ_SIZE);
	client->channel = channel;
	client->socket = socket;
	client->socket->fd = fd;
	return client;
}

bool client_add_elem_at_back(client_list_t front_ptr, client_t new_element)
{
	client_list_t new_node = malloc(sizeof(struct s_client_list));

	new_node->client = new_element;
	new_node->next = NULL;
	if (new_element == NULL)
		return false;
	if (front_ptr == NULL)
		front_ptr->next = new_node;
	else {
		while (true) {
			if (front_ptr->next == NULL) {
				front_ptr->next = new_node;
				break;
			}
			front_ptr = front_ptr->next;
		}
	}
	return true;
}

bool client_del_elem_at_front(client_list_t front_ptr)
{
	client_list_t list = front_ptr;

	if (!list)
		return false;
	front_ptr = list->next;
	free(list);
	return true;
}

bool client_del_elem_by_name(client_list_t list, char *username)
{
	client_list_t list_next = NULL;

	if (!list)
		return false;
	if (!list->next)
		return client_del_elem_at_front(list);
	while (list->next) {
		if (!strcmp(list->next->client->username, username))
			break;
		list = list->next;
	}
	list_next = list;
	list = list->next;
	if (list->next == NULL)
		list_next->next = NULL;
	else
		list_next->next = list->next;
	return true;
}

bool client_del_elem_at_position(client_list_t list, unsigned int position)
{
	client_list_t list_next = NULL;
	unsigned int i = 1;

	if (!list)
		return true;
	while (i < position) {
		list = list->next;
		i++;
	}
	list_next = list;
	list = list->next;
	if (list->next == NULL)
		list_next->next = NULL;
	else
		list_next->next = list->next;
	return true;
}
