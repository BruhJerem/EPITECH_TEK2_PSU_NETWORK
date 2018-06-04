/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** get_next_line
*/


#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char *put_line(char *str, int nb)
{
	char *line;
	int i = -1;
	int k = -1;

	if ((line = malloc(nb + 1)) == NULL)
		return NULL;
	while (++i != nb && nb > 0)
		line[i] = str[i];
	line[i] = '\0';
	if (str[i] != '\0') {
		while (str[i + ++k + 1])
			str[k] = str[k + i + 1];
		str[k] = '\0';
	}
	else
		str[0] = '\0';
	return line;
}

int move_to_backspace(char *str)
{
	int i = -1;
	int k = 0;

	if (str == NULL)
		return -2;
	while (str[++i] && str[i] != '\n')
		++k;
	if (!str[i])
		return -k;
	return k;
}

char *reallocs(char *buff, char *save)
{
	char *new;
	int k = -1;
	int i = -1;

	while (save && save[++k]);
	if (save == NULL)
		k = 0;
	while (buff[++i]);
	if ((new = malloc(k + i + 1)) == NULL)
		return NULL;
	k = -1;
	while (save && save[++k])
		new[k] = save[k];
	if (save == NULL || k == -1)
		k = 0;
	i = -1;
	while (buff[++i])
		new[k + i] = buff[i];
	new[k + i] = '\0';
	if (save)
		free(save);
	return new;
}

char	*read_file(int fd, char *save)
{
	char buff[READ_SIZE + 1];
	int offset = 0;
	int len = 0;

	while (move_to_backspace(save) < 0 &&
		(len = read(fd, buff, READ_SIZE)) > 0) {
		offset += len;
		buff[len] = '\0';
		save = reallocs(buff, save);
	}
	if (len < 0)
		return (NULL);
	if (save && len == 0 && save[0] == '\0') {
		free(save);
		return (NULL);
	}
	return (save);
}

char *get_next_line(const int fd)
{
	static char *save = NULL;
	int i = move_to_backspace(save);

	if (save == NULL || i <= 0) {
		save = read_file(fd, save);
		if ((save = read_file(fd, save)) == NULL)
			return NULL;
		if ((i = move_to_backspace(save)) < 0)
			return put_line(save, -i);
	}
	if (save)
		return put_line(save, move_to_backspace(save));
	return NULL;
}
