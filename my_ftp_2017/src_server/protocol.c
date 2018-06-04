/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** data_transfert
*/

#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>
#include <string.h>
#include "server.h"

/**
* PORT : Initialize port
* @param serv
* @param ip
* @param port_string
*/

static void initialize_port(server_t *serv, char *ip, char *port_string)
{
	int port = (unsigned int)(atoi(port_string) >> 8) *
		(unsigned int)(atoi(port_string) & 0xff);


	if (init_active(serv, ip, port) == 0)
		write_to_client(serv, "200 PORT Command Successful\n");
	else
		write_to_client(serv, "500 Invalid PORT\n");
}

/**
* PORT: Connection and put current mode into PORT
* @param serv
* @param cmd
* @return
*/

bool port_connection(server_t *serv, char **cmd)
{
	char *my_ip = inet_ntoa(serv->s_in_client.sin_addr);

	if (!cmd[1]) {
		write_to_client(serv, "500 PORT Empty\n");
		return false;
	}
	initialize_port(serv, my_ip, cmd[1]);
	serv->data_mode = PORT;
	return true;
}

/**
* PASV: Get into pasv mode & accept
* @param serv
* @return
*/

static bool accept_passiv_server(server_t *serv)
{
	struct protoent *pe = getprotobyname("TCP");
	socklen_t len = sizeof(struct sockaddr_in);
	int fd;

	if (!pe)
		return false;
	fd = accept(serv->fd, (struct sockaddr *) &serv->s_in_client, &len);
	if (fd == -1)
		return false;
	serv->passv_fd = fd;
	serv->data_mode = PASV;
	return true;
}

/**
* PASV :check and give the new port for pasv mode
* @param serv
* @param cmd
* @return
*/

bool passiv_connection(server_t *serv, char **cmd)
{
	(void)cmd;
	char *my_ip = rebind(my_str_to_wordtab(inet_ntoa(
		serv->s_in_client.sin_addr), '.'), ',');
	if (!init_passive(serv, inet_ntoa(serv->s_in_client.sin_addr)))
		return false;
	printf("PASV mode Activated : ip: %s\tPort: %d\n", inet_ntoa(
		serv->s_in_client.sin_addr), serv->port);
	dprintf(serv->client_fd,
		"227 Entering Passive Mode (%s,%d,%d)\n", my_ip,
		(unsigned int) (serv->port >> 8),
		(unsigned int) (serv->port & 0xff));
	if (!accept_passiv_server(serv)) {
		return false;
	}
	return true;
}