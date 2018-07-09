/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Include client
*/

#ifndef PSU_ZAPPY_2017_CLIENT_H
#define PSU_ZAPPY_2017_CLIENT_H

/*
**      REDEFINE EXIT_SUCCESS
*/
#include <stdbool.h>
#include "lib-tools.h"
#include "lib-socket.h"

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
#define NBR_TOT_PORT (65535)
#define RESERVED_PORT (1023)
#define MAX_SIZE_PORT (5)
#define LOCALHOST "127.0.0.1"
#define SHORT_FLAG_PORT "-p"
#define LONG_FLAG_PORT "--port"
#define SHORT_FLAG_NAME "-n"
#define LONG_FLAG_NAME "--name"
#define SHORT_FLAG_HOST "-h"
#define LONG_FLAG_HOST "--host"
#define DEFAULT_SIZE_READ (1024)
#define BUFFSIZE (1024)
#define INIT_HOST(x) t_client x = {.machine = "127.0.0.1", .hash = 0}

/*
**	ERROR MESSAGE
*/
#define HELP USAGE PORT NAME MACHINE
#define USAGE "USAGE:\t./zappy_ai -p port -n name -h machine\n"
#define PORT "\tport\tis the port number\n"
#define NAME "\tname\tis the name of the team\n"
#define MACHINE "\tmachine\tis the name of the machine; localhost by default"
#define ERROR "ERROR : "
#define ERR_PORT ERROR "Invalid port !"
#define ERR_RESERVED_PORT "This port is reserved by the system !"
#define ERR_NAME ERROR "Name must be alphanumerical characters !"
#define ERR_HOST ERROR "Invalid host !"
#define TEAM_KILL "Team %s died !\n"

/*
**	STOP SERVER MESSAGE
*/
#define SIGINTSIGNAL "\"SIGINT\" signal received !"
#define SIGKILLSIGNAL "\"SIGKILL\" signal received !"

/*
**	COMMANDS
*/
#define FORWARD "Forward"
#define RIGHT "Right"
#define LEFT "Left"
#define LOOK "Look"
#define LIST_INVENTORY "Inventory"
#define BROADCAST_TEXT "Broadcast text"
#define CONNECT "Connect_nbr"
#define FORK "Fork"
#define EJECT "Eject"
#define TAKE_OBJ "Take object"
#define SET_OBJ "Set object"
#define INCANTATION "Incantation"
#define EXPECTED_ANSWER "ok"
#define UNEXPECTED_ANSWER "ko"
#define DEAD "dead"
#define SLOT_LEFT "%d slots left int the team\n"
#define DEBUG "Sending : %s on port %d\n"

/*
**	LEVEL MACRO
*/
#define LVL_ONE (0)
#define LVL_TWO (1)
#define LVL_THREE (2)
#define LVL_FOUR (3)
#define LVL_FIVE (4)
#define LVL_SIX (5)
#define LVL_SEVEN (6)

/*
**	LEVEL SCHEMA
*/
static const int lvl[7][6] = {{1, 0, 0, 0, 0, 0},
			      {1, 1, 1, 0, 0, 0},
			      {2, 0, 1, 0, 2, 0},
			      {1, 1, 2, 0, 1, 0},
			      {1, 2, 1, 3, 0, 0},
			      {1, 2, 3, 0, 1, 0},
			      {0, 0, 0, 0, 0, 0},
};

/*
**	PLAYER MACRO
*/
#define NORTH N
#define SOUTH S
#define WEST W
#define EAST E
#define FOOD (0)
#define LINEMATE (1)
#define DERAUMERE (2)
#define SIBUR (3)
#define MENDIANE (4)
#define PHIRA (5)
#define THYSTAME (6)
#define B_NORTH (0)
#define B_NORTH_WEST (1)
#define B_WEST (2)
#define B_SOUTH_WEST (3)
#define B_SOUTH (4)
#define B_SOUTH_EST (5)
#define B_EST (6)
#define B_NORTH_EST (7)

/*
**	CLIENT STRUCTURE
*/
typedef struct s_client {
	int fd;
	int port;
	char *name;
	char *machine;
	long hash;
} t_client;

/*
**	PLAYER STRUCTURE MACRO
*/
#define DIRECTION dir
#define TEAM_NAME team_name
#define INVENTORY inventory
#define MESSAGE msg
#define BROADCAST broadcast
#define LEVEL lvl

/*
**	PLAYER STRUCTURE
*/
typedef struct s_player {
	char DIRECTION;
	char *TEAM_NAME;
	unsigned int INVENTORY[7];
	char *MESSAGE;
	unsigned int BROADCAST;
	int LEVEL;
} t_player;

/*
**	PARSING CLIENT
*/
bool parse_arg_client(int argc, char **argv, t_client *client);
bool port_client(const char *arg, t_client *client);
bool name_client(const char *str, t_client *client);
bool host_client(const char *str, t_client *client);

/*
**	PARSING COMMAND
*/
char **parse_look(char *str);
char **parse_inventory(char *str);
int parse_connect_nbr(const char *str);
unsigned int get_nbr_of(t_player **player, int resource);
bool send_cmd(t_client *client, const char *cmd);
bool cmd_ok(const char *str);
bool cmd_ko(const char *str);
bool is_dead(const char *str);

/*
**	IA
*/
void ia_loop(t_client *client);
bool read_answer(t_client *client, circular_buffer_t buffer);

/*
**	HANDLE CONNECTION
*/
long calc_hash(void);
bool connect_player(t_client *client);

/*
**	SIGNAL
*/
void register_ptr(socket_t socket);
void sig_handler(int sig);
bool handle_signal(void);

/*
**	SOCKET MANIPULATION
*/
bool connect_client_socket(t_client *client);
void destruct_client_socket(t_client *client);
bool create_client_socket(t_client *client);
void copy_client_struct(t_client *client, t_client *new_client);

#endif //PSU_ZAPPY_2017_CLIENT_H
