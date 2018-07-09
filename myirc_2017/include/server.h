/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** Server header
*/

#ifndef PSU_MYIRC_2017_SERVER_H
# define PSU_MYIRC_2017_SERVER_H

# include <stdbool.h>
# include <arpa/inet.h>
# include <sys/poll.h>
# include "common.h"

# define ERR_NEEDMOREPARAMS ":%s 461 %s :This command expects different parameters.\r\n"
# define ERR_ALREADYREGISTERED ":%s 462 %s :Algready registered.\r\n"
# define ERR_NICKNAMEINUSE ":%s 433 %s :Nickname is already in use.\r\n"
# define ERR_NOSUCHNICK ":%s 401 %s :No such nickname / channel.\r\n"

# define RPL_LISTSTART ":%s 321 %s :Channels :Users name\r\n"
# define RPL_LIST ":%s 322 %s :%s\r\n"
# define RPL_LISTEND ":%s 323 %s :End of LIST command.\r\n"

# define RPL_NAMREPLY ":%s 353 %s = %s :%s\r\n"
# define RPL_ENDOFNAMES ":%s 366 %s %s :End of NAMES command.\r\n"

# define ERR_NOSUCHCHANNEL ":%s 403 %s %s :This channel do not exist.\r\n"
# define ERR_NOTONCHANNEL ":%s 442 %s :You are not in this channel.\r\n"

# define RPL_WELCOME ":%s 001 %s :Welcome to IRC\r\n"
# define RPL_MOTDSTART ":%s 375 %s :Message of the day\r\n"
# define RPL_MOTD ":%s 372 %s :Welcome to the server\r\n"
# define RPL_ENDOFMOTD ":%s 376 %s :End of MOTD command.\r\n"
# define RPL_PRIVMSG ":%s!~%s@%s PRIVMSG %s :%s\r\n"

# define RPL_WHOISUSER ":%s 311 %s :%s %s localhost * :%s\r\n"

# define RPL_AUTHENTICATION ":%s 020 %s :Please continue ahead through authentication.\r\n"

# define RPL_JOIN ":%s!~%s@%s JOIN :%s\r\n"
# define RPL_PART ":%s!~%s@%s PART %s :\r\n"
# define RPL_NICK ":%s!~%s@%s NICK :%s %s\r\n"


typedef struct s_client_list *client_list_t;
typedef struct s_client *client_t;
typedef struct s_server *server_t;

typedef struct s_channel_list *channel_list_t;
typedef struct s_channel *channel_t;

enum e_client_status {
	LOGOUT,
	ENTER_USER,
	LOGIN
};

enum e_channel_status {
	PUBLIC
};

struct s_channel {
	char name[25];
	enum e_channel_status status;
	client_list_t client_list; 	// all client in this channel
};

struct s_channel_list {
	channel_t channel;
	channel_list_t next;
};

struct s_client {
	socket_t socket;
	channel_t channel;
	char nickname[25];
	char realname[60];
	char username[25];
	enum e_client_status status;
	char input[READ_SIZE];
};

struct s_client_list {
	client_t client;
	client_list_t next;
};

struct s_server {
	socket_t socket;
	client_list_t client_list;	// all client in server
	channel_list_t channel_list;	// all channels in server
	struct pollfd fds[1024];
	int size_client;
	bool end_server;
	bool compress_fd;
};

/* socket.c */
bool set_bind(socket_t);
bool set_listen(socket_t);
int set_accept(socket_t);

/* init_server.c */
server_t init_server(char **argv);

/* start_process */
void start_process(server_t server);

/* parsing.c */
bool parsing(server_t, char *, int);

/* check_close_connection.c */
void check_close_connection(server_t server, bool close_conn,
			    int current_index);
void close_connection(server_t server, int *nfds);
void close_all_socket(server_t server, int nfds);

/* handle_readable.c */
int handle_readable(server_t server, int index);

/* List Handling for Client */

/* information_client.c */
void client_clear(client_list_t front_ptr);
void client_dump(client_list_t list);

/* action_client.c */
bool client_add_elem_at_back(client_list_t front_ptr, client_t new_element);
bool client_del_elem_at_position(client_list_t front_ptr,
				 unsigned int position);
bool client_del_elem_by_name(client_list_t list, char *username);
client_t create_client(int fd, char *nickname);

/* access_client.c */
client_t client_get_elem_at_front(client_list_t list);
client_t client_get_elem_at_position(client_list_t list, unsigned int position);

client_t client_get_elem_by_nick(client_list_t list, char *name);

/* List Handling for Channel */

/* information_channel.c */
void channel_dump(channel_list_t list);

/* action_channel.c */
bool channel_add_elem_at_back(channel_list_t front_ptr, channel_t new_element);

void channel_clear(channel_list_t front_ptr);
channel_t
create_channel(char *nickname, enum e_channel_status status);

/* access_channel.c */
channel_t channel_get_elem_at_front(channel_list_t list);

channel_t channel_get_elem_by_name(channel_list_t list, char *name);


/* user_registration.c */
bool user_registration(server_t serv, char **cmd, int index);

/* nick_registration.c */
bool nick_registration(server_t server, char **cmd, int index);
void print_welcome(server_t server, client_t client);

/* join.c */
bool join(server_t server, char **cmd, int index);

/* list.c */
bool list(server_t server, char **cmd, int index);

/* part.c */
bool part(server_t server, char **cmd, int index);

/* names.c */
bool names(server_t server, char **cmd, int index);

/* private_msg.c */
bool msg(server_t server, char **cmd, int index);

/* send_client.c */
bool send_to_nick(server_t server, char **cmd, client_t to_client,
		  client_t client);
bool send_to_client_from_channel(char *buffer,
				 server_t server, channel_t channel,
				 client_t c_client);

/* whois.c */
bool whois(server_t server, char **cmd, int index);

/* quit.c */
bool quit(server_t server, char **cmd, int index);
bool handle_disconnect(server_t server, int index);

/* propagation.c */
bool nick_propagation(server_t server, client_t c_client, char *nick,
		      char **cmd);
bool join_propagation(server_t server, client_t c_client, char **cmd);
bool part_propagation(server_t server, client_t c_client, char **cmd);

# endif //PSU_MYIRC_2017_SERVER_H