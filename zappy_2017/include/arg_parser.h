/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server args parser
*/

#ifndef PSU_ZAPPY_2017_SERVER_ARG_PARSER_H
#define PSU_ZAPPY_2017_SERVER_ARG_PARSER_H

#include <unistd.h>
#include <stdbool.h>
#include "types.h"

extern const char *flags_tab[6];

/* DEFINES */

#define ARG_USAGE "Use ./server_zappy -help for more information\n"
#define ARG_ERROR "Error: "
#define ARG_INVALID_ARG_ERROR ARG_ERROR "Invalid arguments\n" ARG_USAGE

/* TYPEDEF */
typedef struct s_arg *arg_t;

/* STRUCTURES */
struct s_arg {
	ushort_t client_nb;
	ushort_t port;
	ushort_t width;
	ushort_t height;
	ushort_t freq;
	char **team_name;
};

/*
** FLAG_P [0]
** FLAG_X [1]
** FLAG_Y [2]
** FLAG_N [3]
** FLAG_C [4]
** FLAG_F [5]
*/
struct s_values {
	int flags[6];
};

void display_help(void);
bool parser_launcher(int, char **, arg_t);
int advanced_isnum(char *);
bool get_port(int, int, char **, arg_t);
bool get_width(int, int, char **, arg_t);
bool get_height(int, int, char **, arg_t);
bool get_client_nb(int, int, char **, arg_t);
bool get_freq(int, int, char **, arg_t);
bool get_team_name(int, int, char **, arg_t);
void init_struct(arg_t);

#endif //PSU_ZAPPY_2017_SERVER_ARG_PARSER_H
