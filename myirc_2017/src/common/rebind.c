/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** rebind
*/

#include <stdlib.h>
#include <string.h>

void free_tab(char **tab)
{
	for (int i = 0; tab[i] != NULL ; ++i)
		free(tab[i]);
	free(tab);
}

char *rebind(char **tab, char separator)
{
	char *s = malloc(sizeof(char) * 30);
	int j = 0;

	if (!tab || !s)
		return NULL;
	if (!tab[1]) {
		s = strdup(tab[0]);
		return s;
	}
	for (int i = 0; tab[i] != NULL ; ++i) {
		for (int k = 0; tab[i][k] != '\0' ; ++k, j++)
			s[j] = tab[i][k];
		if (tab[i + 1] != NULL)
			s[j++] = separator;
	}
	s[j] = '\0';
	return s;
}
