/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Tab functions (char **)
*/

#include <stdlib.h>
#include <string.h>

void free_tab(char **tab)
{
	for (size_t i = 0; tab[i] != NULL; i++)
		free(tab[i]);
	free(tab);
}

size_t tab_len(char **tab)
{
	size_t i = 0;

	while (tab[i] != NULL)
		i++;
	return i;
}

size_t tab_str_len(char **tab)
{
	size_t len = 0;

	for (size_t i = 0; tab[i] != NULL; i++)
		len += strlen(tab[i]);
	return len;
}

char *wordtab_to_str(char **tab, char separator)
{
	size_t len = tab_str_len(tab) + tab_len(tab) + 1;
	char *str = malloc(sizeof(char) * len);
	int j = 0;

	if (!tab || !str)
		return NULL;
	if (!tab[1]) {
		str = tab[0]; // strdup(tab[0]);
		return str;
	}
	for (int i = 0; tab[i] != NULL; ++i) {
		for (int k = 0; tab[i][k] != '\0'; ++k, j++)
			str[j] = tab[i][k];
		if (tab[i + 1] != NULL)
			str[j++] = separator;
	}
	str[j] = '\0';
	return str;
}
