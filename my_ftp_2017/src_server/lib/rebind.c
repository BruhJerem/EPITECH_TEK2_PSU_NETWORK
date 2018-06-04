/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** rebind
*/

#include <stdlib.h>

char *rebind(char **tab, char separator)
{
	char *s = malloc(sizeof(char) * 30);
	int j = 0;

	for (int i = 0; tab[i] != NULL ; ++i) {
		for (int k = 0; tab[i][k] != '\0' ; ++k, j++) {
			s[j] = tab[i][k];
		}
		if (tab[i + 1] != NULL)
			s[j++] = separator;
	}
	s[j] = '\0';
	return s;
}