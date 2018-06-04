/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** server
*/

#ifndef PSU_2017_FTP_SERVER_H
# define PSU_2017_FTP_SERVER_H

# define USERNAME "anonymous"

#include <stdbool.h>
#include <netdb.h>

enum e_data_mode {
	NONE,
	PASV,
	PORT
};

/**
* EMPTY: Here no Username and passw enter
* USER: Here user enter
* READY: here user & passw enter: need check if passw and user match
* COMPLETE: already connected
*/

enum e_connection_status {
	EMPTY,
	USER,
	READY,
	COMPLETE
};

typedef struct s_path {
	char *home;
	char *curr;
} path_t;


typedef struct s_connection {
	enum e_connection_status is_connected;
	char *usename_cmd;
	char *password_cmd;
} connection_t;

typedef struct s_server {
	int fd;
	int client_fd;
	int passv_fd;
	unsigned short port;
	struct sockaddr_in s_in_client;
	connection_t *connection;
	path_t *path;
	enum e_data_mode data_mode;
} server_t;

/* start_server.c */
int server(char **av);
bool start_server(server_t *serv);
server_t *accept_server(server_t *serv);
bool listen_server(server_t *serv, int max_client);

/* init_protocol.c */
int init_active(server_t *serv, char *ip, int port);
bool init_passive(server_t *serv, char *ip);

/* user_handling.c */
bool handling_user_connection(server_t *serv, char **cmd);

/* check_user.c */
bool check_connected(server_t *serv, char *cmd);
bool check_status(server_t *serv, char **cmd);

/* communicate_client.c */
bool write_to_client(server_t *serv, char *message);
bool read_from_client(server_t *serv);

/* lib */
char *epur_str(char *str);
char **my_str_to_wordtab(char *str, char separator);
char *rebind(char **tab, char separator);

/* help_noop_quit.c */
bool noop_function(server_t *serv, char **cmd);
bool quit_function(server_t *serv, char **cmd);
bool help_function(server_t *serv, char **cmd);

/* directory.c */
bool pwd_function(server_t *serv, char **cmd);
bool cwd_function(server_t *serv, char **cmd);
bool cdup_function(server_t *serv, char **cmd);

/* protocol.c */
bool passiv_connection(server_t *serv, char **cmd);
bool port_connection(server_t *serv, char **cmd);

/* list_function */
bool list_function(server_t *serv, char **cmd);

/* delete_file.c */
bool dele_function(server_t *serv, char **cmd);
int is_regular_file(const char *path);
bool check_before(server_t *serv, const char *filename);

/* stor_function.c */
bool stor_function(server_t *serv, char **cmd);

/* retr_function.c */
bool retr_function(server_t *serv, char **cmd);

/* utils.c */
size_t size_current_path(void);
bool find_home_path(server_t *serv, const char *path);
bool directory_exists(const char *filename);

#endif //PSU_2017_FTP_SERVER_H
