/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** communicate_client
*/

#include <zconf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "lib/get_next_line.h"

/**
* All the command in string
*/

static const char *function_command[] = {"user", "pass", "cwd", "cdup", "quit",
"dele", "pwd", "pasv", "port", "help", "noop", "retr", "stor", "list"};

/**
* Function pointer in array
*/

static bool (**fpts(void))(server_t *serv, char **cmd)
{
	bool (**pts)(server_t *serv, char **cmd);

	pts = malloc(14 * sizeof(*pts));
	pts[0] = &handling_user_connection;
	pts[1] = &handling_user_connection;
	pts[2] = &cwd_function;
	pts[3] = &cdup_function;
	pts[4] = &quit_function;
	pts[5] = &dele_function;
	pts[6] = &pwd_function;
	pts[7] = &passiv_connection;
	pts[8] = &port_connection;
	pts[9] = &help_function;
	pts[10] = &noop_function;
	pts[11] = &retr_function;
	pts[12] = &stor_function;
	pts[13] = &list_function;
	return pts;
}

/**
* Function to write into the client
* @param serv
* @param message
* @return
*/

bool write_to_client(server_t *serv, char *message)
{
	if (write(serv->client_fd, message, strlen(message)) < 0)
		return false;
	return true;
}

/**
* Function to find the command into the input of client
* @param serv
* @param cmd
* @return
*/

static bool find_command(server_t *serv, char **cmd)
{
	bool (**pts[14])(server_t *, char **);

	pts[0] = fpts();
	printf("Command received: %s\n", cmd[0]);
	for (int i = 0; function_command[i]; ++i) {
		if (!strcasecmp(function_command[i], cmd[0])) {
			if (i == 4) {
				return !(*pts[0][i])(serv, cmd) ? false : true;
			}
			if (i > 1 && !check_connected(serv, cmd[0])) {
				return false;
			}
			return !(*pts[0][i])(serv, cmd) ? false : true;
		}
	}
	write_to_client(serv, serv->connection->is_connected != COMPLETE
			? "530 Please login with "
		"USER and PASS.\n" : "500 Unknown command.\n");
	return true;
}

/**
* Free tab given in param
* @param t
*/

static void free_tab(char **t)
{
	for (int i = 0; t[i]; ++i) {
		free(t[i]);
	}
	free(t);
}

/**
* Read the input from client (loop for one server)
* @param serv
* @return
*/

bool read_from_client(server_t *serv)
{
	char **cmd;
	char *buffer;

	while (true) {
		buffer = get_next_line(serv->client_fd);
		if (buffer[0] == ' ') {
			write_to_client(serv, serv->connection->is_connected
					!= COMPLETE
					? "530 Please login with "
					"USER and PASS.\n" :
					"500 Unknown command.\n");
			free(buffer);
			continue;
		}
		cmd = my_str_to_wordtab(epur_str(buffer), ' ');
		if (!cmd) {
			continue;
		}
		find_command(serv, cmd);
		free_tab(cmd);
	}
}
