/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Error display
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "arg_parser.h"

void display_help(void)
{
	printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2"
	       " ...  -c clientsNb -f freq\n");
	printf("\tport\t\tis the port number\n");
	printf("\twidth\t\tis the width of the world\n");
	printf("\theight\t\tis the height of the world\n");
	printf("\tnameX\t\tis the name of the team X\n");
	printf("\tclientsNb\tis the number of authorized clients");
	printf(" per team\n");
	printf("\tfreq\t\tis the reciprocal of time unit for");
	printf(" execution of actions\n");
}
