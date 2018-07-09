/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Server include
*/

#ifndef PSU_ZAPPY_2017_SERVER_H
#define PSU_ZAPPY_2017_SERVER_H

#include <stdbool.h>
#include <poll.h>
#include "lib-socket.h"
#include "arg_parser.h"

/* DEFINES */
#define READ_SIZE 1024

// Ui client authentication
#define UI_CONNECTION_MSG "GRAPHIC"
#define UI_CONNECTION_MSG_SIZE 8

// Server messages
#define S_CONNECTION_WELCOME "New incoming connection -> fd : %d\n"
#define S_CONNECTION_REFUSED "Client connection refused\n"

// Client messages
#define C_CONNECTION_WELCOME "WELCOME\n"
#define C_CONNECTION_REFUSED "Connection refused by the server\n"
#define C_ARGUMENT_ERROR "Error: Wrong Argument\n"

// Player client command
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

// UI client command input/output
#define C_MSZ "msz %zu %zu\n"
#define C_BCT "bct %lu %lu %d %d %d %d %d %d %d\n"
#define C_TNA "tna %s\n"
#define C_PPO "ppo %d %lu %lu %d\n"
#define C_PLV "plv %d %d\n"
#define C_PIN "pin %d %lu %lu %d %d %d %d %d %d %d\n"

// UI client command only output
#define C_SGT "sgt %d\n"
#define C_PNW "pnw %d %lu %lu %d %d %s\n"
#define C_PDI "pdi %d\n"

// Look struct init define
#define INIT_LOOK(look) look_t look = {.x = 0, .y = 0, .start = 0, .end = 0}

/* TYPEDEFS */
typedef struct s_ui_client *ui_client_t;
typedef struct s_player_client *player_client_t;
typedef struct s_player_client_list *player_client_list_t;
typedef struct s_team *team_t;
typedef struct s_team_list *team_list_t;
typedef struct s_inventory *inventory_t;
typedef struct s_map *map_t;
typedef struct s_tile *tile_t;
typedef struct s_server *server_t;

typedef struct s_look look_t;

/* ENUMS */
enum e_player_orientation {
	NORTH = 1,
	EAST = 2,
	SOUTH = 3,
	WEST = 4
} player_orientation;

enum e_player_state {
	AWAITING_TEAM_NAME,
	ONLINE
};

/* STRUCTURES */
struct s_look {
	int x;
	int y;
	int start;
	int end;
};

struct s_ui_client {
	socket_t socket;
	nfds_t poll_idx;
	char buffer[READ_SIZE];
};

struct s_player_client {
	socket_t socket;
	nfds_t poll_idx;
	ushort_t id;
	inventory_t inventory;
	char *team_name;
	char buffer[READ_SIZE];
	enum e_player_state state;
	ushort_t level;
	size_t x;
	size_t y;
	enum e_player_orientation orientation;
};

struct s_player_client_list {
	player_client_t player;
	player_client_list_t next;
};

struct s_inventory {
	ushort_t food;
	ushort_t linemate;
	ushort_t deraumere;
	ushort_t sibur;
	ushort_t mendiane;
	ushort_t phiras;
	ushort_t thystame;
};

struct s_team {
	char *name;
	ushort_t nbr_player;
};

struct s_team_list {
	team_t team;
	team_list_t next;
};

struct s_tile {
	size_t x;
	size_t y;
	inventory_t inventory;
};

struct s_map {
	size_t height;
	size_t width;
	size_t nbr_item;
	tile_t *tiles;
};

struct s_server {
	socket_t socket;
	struct pollfd poll_fds[1024];
	nfds_t nfds;
	map_t map;
	team_list_t teams;
	ui_client_t ui;
	player_client_list_t players;
	ushort_t action_freq;
	size_t timeout;
	ushort_t nbr_player_max_team;
	ushort_t nbr_player;
	bool compress_fd;
};

/* FUNCTIONS */

/* Server base functions */
server_t init_server(arg_t);
bool server_loop(server_t server);

/* Map functions */
map_t init_map(size_t height, size_t width);
void debug_map(map_t map);
void free_map(map_t map);
int get_tile_index(map_t map, int y, int x);

/* Map generation functions */
bool generate_map(map_t map);

/* Map player */
ushort_t count_player_in_pos(server_t server, size_t y, size_t x);

/* Map player generation */
void gen_player_information(map_t map, player_client_t player_client);

/* Map player orientation */
void forward_player(map_t map, player_client_t player);
void left_player(player_client_t player);
void right_player(player_client_t player);

/* Map player vision */
void player_look_tiles(server_t server, player_client_t player);

/* Incoming connection */
bool incoming_connection(server_t server);

/* Handle readable */
bool handle_readable(server_t server, size_t index);
bool handle_disconnection(server_t server, size_t index);

/* Inventory */
inventory_t create_inventory(void);
void send_tile_inventory(tile_t tile, int fd);
void send_tiles_inventory(server_t server, int fd);
void send_player_inventory(player_client_t player, int fd);

/* Player */
player_client_t create_player_client(server_t server, socket_t socket,
				nfds_t idx);

/* Player list */
bool add_player(player_client_list_t *list, player_client_t new_element);
bool delete_player_by_fd(player_client_list_t *list, int idx);
player_client_t get_player_by_fd(player_client_list_t list, int idx);
player_client_t get_player_by_id(player_client_list_t list, size_t id);

/* Team */
team_list_t init_team_list(char **teams_name);
void send_teams(server_t server, int fd);

/* Team list */
team_t get_team_by_name(team_list_t list, char *name);
bool add_team(team_list_t front_ptr, team_t new_element);
bool delete_team_at_pos(team_list_t *teams, int position);

/* UI client */
ui_client_t create_ui_client(server_t server, socket_t socket, nfds_t idx);
bool add_ui_to_server(server_t server, player_client_t cur_player, size_t idx);

/* Command Router */
bool command_router(server_t server, char *buffer, size_t index);
bool route_command_player(server_t server, char **cmd, int index);
bool route_command_ui(server_t server, char **cmd, int index);

/* Server debug */
void debug_server(server_t server);

/* Events */
void player_connect_event(server_t server, player_client_t player);
void player_disconnect_event(server_t server, player_client_t player);
void player_move_event(server_t server, player_client_t player);

/* Command Function UI */
bool msz(server_t server, char **cmd, int index);
bool bct(server_t server, char **cmd, int index);
bool mct(server_t server, char **cmd, int index);
bool tna(server_t server, char **cmd, int index);
bool ppo(server_t server, char **cmd, int index);
bool plv(server_t server, char **cmd, int index);
bool pin(server_t server, char **cmd, int index);
bool sgt(server_t server, char **cmd, int index);
bool sst(server_t server, char **cmd, int index);

/* Command Function Player */
bool broadcast_text(server_t server, char **cmd, int index);
bool eject(server_t server, char **cmd, int index);
bool fork_player(server_t server, char **cmd, int index);
bool forward(server_t server, char **cmd, int index);
bool incantation(server_t server, char **cmd, int index);
bool inventory(server_t server, char **cmd, int index);
bool left(server_t server, char **cmd, int index);
bool look(server_t server, char **cmd, int index);
bool right(server_t server, char **cmd, int index);
bool set_object(server_t server, char **cmd, int index);
bool take_object(server_t server, char **cmd, int index);
bool connect_player(server_t server, char **cmd, int index);

#endif //PSU_ZAPPY_2017_SERVER_H
