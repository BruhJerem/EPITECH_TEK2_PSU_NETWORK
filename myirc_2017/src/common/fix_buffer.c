/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** epur_str
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
* Fix the buffer with \r
* @param buffer to fix
*/

void fix_buffer(char *buffer)
{
	int i = 0;

	if (!buffer)
		return;
	while (buffer[i] != '\r' && buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	buffer[i] = '\0';
}
