/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Tab len function
*/

#include <stdlib.h>

size_t tab_len(char **tab)
{
	size_t i = 0;

	while (tab[i])
		i++;
	return i;
}
