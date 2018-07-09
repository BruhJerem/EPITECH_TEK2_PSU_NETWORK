/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** str_to_wordtab
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

static bool check_separators(char c, char delimiter)
{
	if (c == delimiter || c == '\0' || c == '\n')
		return false;
	return true;
}

static int count_words(char *str, char delimiter)
{
	int nb_words = 0;
	int i = 0;

	while (str[i] != '\0') {
		if (check_separators(str[i], delimiter)) {
			while (check_separators(str[i], delimiter))
				i++;
			nb_words++;
		}
		if (str[i] != '\0')
			i++;
	}
	return nb_words;
}

static bool malloc_words(char **tab, char *str, char delimiter)
{
	int n_word = 0;
	int nb_letters = 0;
	int i = 0;

	while (str[i] != '\0') {
		if (check_separators(str[i], delimiter)) {
			nb_letters = 0;
			while (check_separators(str[i], delimiter)) {
				nb_letters++;
				i++;
			}
			tab[n_word] = malloc(sizeof(char) * nb_letters + 1);
			if (tab[n_word] == NULL)
				return (true);
			n_word++;
		}
		if (str[i] != '\0')
			i++;
	}
	return false;
}

static void fill_tab(char **tab, char *str, char delimiter)
{
	int n_word = 0;
	int n_letter = 0;
	int i = 0;

	while (str[i] != '\0') {
		if (check_separators(str[i], delimiter)) {
			n_letter = 0;
			while (check_separators(str[i], delimiter)) {
				tab[n_word][n_letter] = str[i];
				n_letter++;
				i++;
			}
			tab[n_word][n_letter] = '\0';
			n_word++;
		}
		if (str[i] != '\0')
			i++;
	}
}

char **str_to_wordtab(char *str, char delimiter)
{
	char **tab = NULL;
	int nb_words = 0;

	if (str == NULL)
		return (NULL);
	nb_words = count_words(str, delimiter);
	tab = malloc(sizeof(*tab) * (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	if (malloc_words(tab, str, delimiter) != false)
		return (NULL);
	fill_tab(tab, str, delimiter);
	tab[nb_words] = NULL;
	return tab;
}
