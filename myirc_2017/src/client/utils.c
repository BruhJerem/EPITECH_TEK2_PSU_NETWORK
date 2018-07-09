/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Utils functions
*/

#include <string.h>
#include <ctype.h>
#include "common.h"

void str_to_upper(char *str)
{
	while ((*str = (char) toupper(*str)))
		++str;
}

char *transform_command(char **command)
{
	char *buffer = NULL;

	memmove(&command[0][0], &command[0][1], strlen(command[0]));
	command[0][strlen(command[0])] = '\0';
	str_to_upper(command[0]);
	buffer = rebind(command, ' ');
	return buffer;
}
