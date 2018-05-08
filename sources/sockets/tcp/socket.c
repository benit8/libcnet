/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / socket.c
*/

#include "cnet/tcp_socket.h"

tcp_socket_t *tcp_socket_bare(void)
{
	return ((tcp_socket_t *)socket_bare(SOCKET_TCP));
}

tcp_socket_t *tcp_socket_create(void)
{
	return ((tcp_socket_t *)socket_create(SOCKET_TCP));
}

bool tcp_socket_create_handle(tcp_socket_t *sock)
{
	return (socket_create_handle((socket_t *)sock));
}

bool tcp_socket_create_from_handle(tcp_socket_t *sock, int handle)
{
	return (socket_create_from_handle((socket_t *)sock, handle));
}

void tcp_socket_destroy(tcp_socket_t *sock)
{
	tcp_socket_disconnect(sock);
	socket_destroy((socket_t *)sock);
}