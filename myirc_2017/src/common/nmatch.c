/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** match
*/

int nmatch(char *s1, char *s2)
{
	if (*s2 == '\0')
		return *s1 == '\0';
	if (*s1 == '\0' && *s2 == '*')
		return nmatch(s1, s2 + 1);
	if (*s1 == *s2)
		return nmatch(s1 + 1, s2 + 1);
	if (*s2 == '*')
		return nmatch(s1 + 1, s2) + nmatch(s1, s2 + 1);
	if (*s2 != *s1)
		return 0;
	return 1;
}
