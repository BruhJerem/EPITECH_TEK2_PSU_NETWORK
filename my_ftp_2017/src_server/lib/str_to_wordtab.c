/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** str_to_wordtab
*/

#include <stdlib.h>
#include <string.h>

static char **malloc_tab_str(char **tab, const char *str, char cut)
{
	int k = -1;
	int o = 0;
	int i = -1;

	while (str[++k]) {
		o += (str[k] != cut ? 1 : 0);
		if (str[k] == cut || str[k + 1] == '\0') {
			if ((tab[++i] = malloc(o + 1)) == NULL)
				return NULL;
			tab[i][o] = '\0';
			o = 0;
		}
	}
	return tab;
}

static char **malloc_tab(char *str, char cut)
{
	char **tab;
	int i = -1;
	int k = 1;

	while (str[++i]) {
		if (str[i] == cut)
			k++;
	}
	if ((tab = malloc(sizeof(char *) * (k + 1))) == NULL)
		return NULL;
	tab[k] = NULL;
	tab = malloc_tab_str(tab, str, cut);
	return tab;
}

static char *malloc_clear(char *str, char remove_char, char cut)
{
	char *new;
	int i = -1;
	int mall = 0;

	while (str[++i]) {
		if (str[i] == remove_char ||
			(str[i] == cut && str[i + 1] && str[i + 1] == cut) ||
			(str[i] == cut && !str[i + 1]))
			++mall;
	}
	if ((new = malloc(strlen(str) - mall + 1)) == NULL)
		return NULL;
	return new;
}

static char *clear_str(char *str, char remove_char, char cut)
{
	char *new = malloc_clear(str, remove_char, cut);
	int i = -1;
	int k = -1;

	while (str[++i] == remove_char || str[i] == cut);
	i--;
	while (str[++i]) {
		if (str[i] != remove_char &&
			!(str[i] == cut && str[i + 1] && str[i + 1] == cut) &&
			!((str[i] == cut && !str[i + 1])))
			new[++k] = str[i];
	}
	new[k + 1] = '\0';
	return new;
}

char **my_str_to_wordtab(char *str, char separator)
{
	char **tab;
	int i = 0;
	int k = -1;
	int o = -1;

	if (str == NULL || str[0] == '\0')
		return NULL;
	str = clear_str(str, 0, separator);
	tab = malloc_tab(str, separator);
	while (str[++k] != '\0') {
		if (str[k] == separator) {
			++i;
			tab[i][o] = '\0';
			o = -1;
		} else
			tab[i][++o] = str[k];
	}
	return tab;
}
