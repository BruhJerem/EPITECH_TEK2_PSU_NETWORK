/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** init_protocol
*/

#include <arpa/inet.h>
#include <zconf.h>
#include "server.h"

/**
* Fill port into struct server_t
* @param serv
* @param s_in
*/

static void get_port(server_t *serv, struct sockaddr_in *s_in)
{
	socklen_t len = sizeof(s_in);

	getsockname(serv->fd, (struct sockaddr *) s_in, &len);
	serv->port = ntohs(s_in->sin_port);
}

/**
* PASV: Initialize new server
* @param serv
* @param ip
* @return
*/

bool init_passive(server_t *serv, char *ip)
{
	struct sockaddr_in s_in;
	struct protoent *pe = getprotobyname("TCP");

	if (!pe)
		return -1;
	serv->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (serv->fd == -1)
		return -1;
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(0);
	s_in.sin_addr.s_addr = inet_addr(ip);
	if (bind(serv->fd, (const struct sockaddr *) &s_in,
		sizeof(s_in)) == -1) {
		if (close(serv->fd) == -1)
			return false;
		return false;
	}
	serv->s_in_client = s_in;
	get_port(serv, &s_in);
	return listen_server(serv, 42);
}

/**
* PORT: Initialize new server
* @param serv
* @param ip
* @param port
* @return
*/

int init_active(server_t *serv, char *ip, int port)
{
	struct sockaddr_in s_in;
	struct protoent *pe = getprotobyname("TCP");

	if (!pe)
		return -1;
	serv->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (serv->fd == -1)
		return -1;
	setsockopt(serv->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	serv->passv_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	return (connect(serv->passv_fd,
			(const struct sockaddr *) &s_in, sizeof(s_in)));
}