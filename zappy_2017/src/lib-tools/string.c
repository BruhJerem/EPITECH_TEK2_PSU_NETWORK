/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** String functions
*/

#include <unistd.h>
#include <string.h>

char *ov_strcat(char *dest, char *src, size_t overwrite_n)
{
	size_t idx = 0;
	size_t idx_edit = 0;
	char *ptr = src;

	while (idx < overwrite_n) {
		idx_edit = strlen(dest) - (overwrite_n - idx);
		dest[idx_edit] = src[idx];
		idx++;
		ptr++;
	}
	strcat(dest, ptr);
	return dest;
}
