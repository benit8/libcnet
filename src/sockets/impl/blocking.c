/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / impl / blocking.c
*/

#include "socket.h"

void socket_set_blocking(socket_t *sock, bool blocking)
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

bool socket_is_blocking(socket_t *sock)
{
	return (sock->blocking);
}