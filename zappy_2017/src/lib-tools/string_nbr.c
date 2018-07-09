/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** String number functions
*/

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool str_is_number(const char *str)
{
	if (str == NULL)
		return false;
	while (*str != '\0') {
		if (!isdigit(*str))
			return false;
		str++;
	}
	return true;
}
