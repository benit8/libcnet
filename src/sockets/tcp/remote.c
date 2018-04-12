/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / remote.c
*/

#include "tcp_socket.h"

static struct sockaddr_in *tcp_socket_get_remote_infos(tcp_socket_t *sock)
{
	static struct sockaddr_in address;
	socklen_t size = sizeof(address);

	if (sock->handle == -1)
		return (NULL);
	if (getpeername(sock->handle, (struct sockaddr *)&address, &size) != -1)
		return (&address);
	return (NULL);
}

ip_address_t tcp_socket_get_remote_address(tcp_socket_t *sock)
{
	struct sockaddr_in *address = tcp_socket_get_remote_infos(sock);

	return (address ? address->sin_addr.s_addr : IP_NONE);
}

unsigned short tcp_socket_get_remote_port(tcp_socket_t *sock)
{
	struct sockaddr_in *address = tcp_socket_get_remote_infos(sock);

	return (address ? ntohs(address->sin_port) : 0);
}