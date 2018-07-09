/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular buffer
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "lib-tools.h"

bool circular_buf_reset(circular_buffer_t cbuf)
{
	if (!cbuf)
		return false;
	cbuf->head = 0;
	cbuf->tail = 0;
	return true;
}

bool circular_buf_is_empty(circular_buffer_t cbuf)
{
	return cbuf->head == cbuf->tail;
}

bool circular_buf_is_full(circular_buffer_t cbuf)
{
	return ((cbuf->head + 1) % cbuf->size) == cbuf->tail;
}

bool circular_buf_put(circular_buffer_t cbuf, char *data)
{
	if (!cbuf || !data)
		return false;
	size_t max_head = cbuf->head + strlen(data);
	int j = 0;

	for (size_t i = cbuf->head; i < max_head; i++) {
		if (max_head >= cbuf->size && i == cbuf->size) {
			i = 0;
			max_head = max_head % cbuf->size;
		}
		cbuf->buffer[i] = data[j];
		j++;
	}
	cbuf->head = max_head % cbuf->size;

	if (cbuf->head == cbuf->tail)
		cbuf->tail = (cbuf->tail + strlen(data)) % cbuf->size;
	return true;
}

static size_t get_pos_new_line(circular_buffer_t cbuf)
{
	size_t i = cbuf->tail;

	while (i < cbuf->size) {
		if (cbuf->buffer[i] == '\n')
			return i;
		i++;
	}
	return 0;
}

char *circular_buf_get(circular_buffer_t cbuf)
{
	if (!cbuf || circular_buf_is_empty(cbuf))
		return NULL;
	size_t i = cbuf->tail;
	size_t max_tail = get_pos_new_line(cbuf);
	char *buffer = malloc(sizeof(char) * (max_tail - cbuf->tail) + 1);
	int j = 0;

	if (!buffer)
		return NULL;
	for (; i < max_tail; i++) {
		buffer[j] = cbuf->buffer[i];
		j++;
	}
	buffer[i] = '\0';
	cbuf->tail = (max_tail + 1) % cbuf->size;
	return buffer;
}

circular_buffer_t create_circular_buf(size_t size)
{
	circular_buffer_t cbuf = malloc(sizeof(struct s_circular_buffer));

	if (!cbuf) {
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}
	cbuf->buffer = malloc(sizeof(char) * size);
	if (!cbuf->buffer) {
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}
	cbuf->size = size;
	cbuf->tail = 0;
	cbuf->head = 0;
	return cbuf;
}

bool free_circular_buf(circular_buffer_t cbuf)
{
	if (cbuf) {
		if (cbuf->buffer)
			free(cbuf->buffer);
		free(cbuf);
		return true;
	}
	return false;
}
