/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** epur_str
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* Epur string only \r
* @param str string to epur
* @return
*/

char *epur_str(char *str)
{
	char *ret;
	int k = 0;
	int i = 0;

	if (!str || !(ret = calloc(sizeof(ret), (strlen(str) + 4))))
		return NULL;
	while (str[i] == '\r' && str[i] != '\0')
		i++;
	while (str[i] != '\0') {
		while (!(str[i] > 32 && str[i] < 127) && str[i] != '\0')
			i++;
		while (str[i] > 32 && str[i] < 127 &&
			str[i] != '\r' && str[i] != '\0')
			ret[k++] = str[i++];
		ret[k++] = ' ';
		if (str[i - 1] == '\r')
			k--;
	}
	ret[k++] = '\0';
	return ret;
}

