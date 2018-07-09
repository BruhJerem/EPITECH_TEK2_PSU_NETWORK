/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Lib Socket header file
*/

#ifndef PSU_ZAPPY_2017_LIB_SOCKET_H
#define PSU_ZAPPY_2017_LIB_SOCKET_H

#include <unistd.h>
#include <stdbool.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Socket struct */
typedef struct s_socket *socket_t;

struct s_socket {
	int fd;
	char *address;
	ushort_t port;
};

/* Socket functions */
bool bind_socket(socket_t);
bool listen_socket(socket_t);
socket_t accept_socket(socket_t);
bool connect_socket(socket_t socket);
socket_t create_socket(char *address, ushort_t port, bool re_use_addr);
bool destruct_socket(socket_t socket);
bool disconnect_socket(socket_t socket);

#ifdef __cplusplus
};
#endif

#endif //PSU_ZAPPY_2017_LIB_SOCKET_H
