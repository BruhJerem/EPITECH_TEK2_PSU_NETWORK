/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Include parsing server
*/

#ifndef PSU_ZAPPY_2017_CLIENT_H
#define PSU_ZAPPY_2017_CLIENT_H

/*
**      REDEFINE EXIT_SUCCESS
*/
#include <stdbool.h>

#ifdef EXIT_SUCCESS
#undef EXIT_SUCCESS
	#define EXIT_SUCCESS (0)
#else
	#define EXIT_SUCCESS (0)
#endif

/*
**      REDEFINE EXIT_FAILURE
*/
#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
	#define EXIT_FAILURE (84)
#else
	#define EXIT_FAILURE (84)
#endif

/*
**	CONSTANT
*/
#define UNUSED (void)
#define NBR_TOT_PORT (65535)
#define RESERVED_PORT (1023)
#define MAX_SIZE_PORT (5)
#define MAX_SIZE_MAP (1000)
#define MAX_NB_CLIENT (1024)
#define MIN_ARG_SERVER (13)
#define MIN_FREQ (0.1)
#define MAX_FREQ (10)
#define SHORT_FLAG_PORT "-p"
#define LONG_FLAG_PORT "--port"
#define FLAG_WIDTH "-x"
#define FLAG_HEIGHT "-y"
#define SHORT_FLAG_NAME "-n"
#define LONG_FLAG_NAME "--name"
#define FLAG_CLIENT_NB "-c"
#define FLAG_FREQ "-f"

/*
**	HELP MESSAGE
*/
#define HELP_SERVER HELP_ _HELP
#define HELP_ USAGE_S_ _USAGE_S PORT_S WIDTH_S _HELP HEIGHT_S NAME_S
#define _HELP CLIENT_NB_S_ _CLIENT_NB_S FREQ_S_ _FREQ_S
#define USAGE_S_ "USAGE: ./zappy_server -p port -x width -y height -n "
#define _USAGE_S "name1 name2 ... -c clientsNb -f freq\n"
#define PORT_S "port\tis the port number\n"
#define WIDTH_S "width\tis the width of the world\n"
#define HEIGHT_S "height\tis the height of the world\n"
#define NAME_S "nameX\tis the name of the team X\n"
#define CLIENT_NB_S_ "clientsNb\tis the number of authorized clients per
#define _CLIENT_NB_S "team\n"
#define FREQ_S_ "freq\tis the reciprocal of time unit for execution
#define _FREQ_S "of actions\n"
/*
**	ERROR MESSAGE
*/
#define ERROR "ERROR : "
#define ERR_PORT ERROR "Invalid port !"
#define ERR_RESERVED_PORT "This port is reserved by the system !"
#define ERR_NAME ERROR "Name must be alphanumerical characters !"
#define ERR_HOST ERROR "Invalid host !"
#define ERR_WIDTH ERROR "Invalid width !"
#define ERR_HEIGHT ERROR "Invalid height !"
#define ERR_NB_CLIENT ERROR "Too much client !"
#define ERR_FREQ ERROR "Invalid frequency !"

/*
**	CLIENT STRUCTURE
*/
typedef struct s_client {
	int port;
	char *name;
	char *machine;
} t_client;

/*
**	PARSING
*/
bool parse_arg_server(int argc, char **argv, server_t **server);
bool port_server(const char *arg, server_t **server);
bool name_server(const char *str, server_t **server);
bool width_server(const char *str, server_t **server);
bool height_server(const char *str, server_t **server);
bool nb_client_server(const char *str, server_t **server);
bool freq_server(const char *str, server_t **server);

#endif //PSU_ZAPPY_2017_CLIENT_H
