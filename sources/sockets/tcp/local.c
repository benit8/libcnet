/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / local.c
*/

#include "cnet/tcp_socket.h"

static struct sockaddr_in *tcp_socket_get_local_infos(tcp_socket_t *sock)
{
	static struct sockaddr_in address;
	socklen_t size = sizeof(address);

	if (sock->handle == -1)
		return (NULL);
	if (getsockname(sock->handle, (struct sockaddr *)&address, &size) != -1)
		return (&address);
	return (NULL);
}

unsigned short tcp_socket_get_local_port(tcp_socket_t *sock)
{
	struct sockaddr_in *address = tcp_socket_get_local_infos(sock);

	return (address ? ntohs(address->sin_port) : 0);
}