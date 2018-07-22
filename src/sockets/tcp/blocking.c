/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / blocking.c
*/

#include "cnet/tcp_socket.h"

void tcp_socket_set_blocking(tcp_socket_t *sock, bool blocking)
{
	socket_set_blocking((socket_t *)sock, blocking);
}

bool tcp_socket_is_blocking(tcp_socket_t *sock)
{
	return (sock->blocking);
}