/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / blocking.c
*/

#include "tcp_socket.h"

void tcp_socket_set_blocking(tcp_socket_t *sock, bool blocking)
{
	int status;

	if (sock->handle == -1)
		return;
	status = fcntl(sock->handle, F_GETFL);
	if (blocking) {
		if (fcntl(sock->handle, F_SETFL, status & ~O_NONBLOCK) == -1)
			ERR("failed to block socket: %s", strerror(errno));
	}
	else {
		if (fcntl(sock->handle, F_SETFL, status | O_NONBLOCK) == -1)
			ERR("failed to unblock socket: %s", strerror(errno));
	}
	sock->blocking = blocking;
}

bool tcp_socket_is_blocking(tcp_socket_t *sock)
{
	return (sock->blocking);
}