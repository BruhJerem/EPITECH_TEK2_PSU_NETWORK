/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Client header
*/

#ifndef PSU_MYIRC_2017_CLIENT_H
#define PSU_MYIRC_2017_CLIENT_H

#include <poll.h>
#include "common.h"

// Macros
#define BUFF_SIZE 1024
#define NBR_COMMANDS 12
#define CS_CONNECTED "Connected to server %s on port %u\n"
#define CS_FAILED "Failed to connect to server\n"

// Structures
typedef struct s_client *client_t;

struct s_client {
	char *username;
	struct pollfd fds[2];
	nfds_t nfds;
	socket_t socket;
};

// Client functions
client_t init_client(void);
void client_loop(client_t client);
void route_command(client_t client, char *buffer);

// Socket functions
bool connect_socket(socket_t socket);

// Commands
bool command_help(client_t client, char **command);
bool command_quit(client_t client, char **command);

bool command_server(client_t client, char **command);
bool command_list(client_t client, char **command);
bool command_users(client_t client, char **command);
bool command_disconnect(client_t client, char **command);

bool command_join(client_t client, char **command);
bool command_part(client_t client, char **command);
bool command_names(client_t client, char **command);

bool command_nick(client_t client, char **command);
bool command_msg(client_t client, char **command);
bool command_accept_file(client_t client, char **command);

// Action
void send_message(client_t client, char *line);
bool handling_event(client_t client);
bool send_command_to_server(int server_fd, char **command);


// Check
bool check_server_connected(client_t client, char *start_cmd);

// Utils
void str_to_upper(char *str);
char *transform_command(char **command);


#endif //PSU_MYIRC_2017_CLIENT_H
