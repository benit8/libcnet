/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / impl / socket.c
*/

#include "cnet/socket.h"

socket_t *socket_create(socket_type_t type)
{
	socket_t *sock = socket_bare(type);

	if (!sock)
		return (NULL);
	if (!socket_create_handle(sock)) {
		free(sock);
		return (NULL);
	}
	return (sock);
}

socket_t *socket_bare(socket_type_t type)
{
	socket_t *sock = calloc(1, sizeof(socket_t));

	if (!sock) {
		ERR("out of memory");
		return (NULL);
	}
	sock->type = type;
	sock->handle = -1;
	sock->blocking = true;
	return (sock);
}

bool socket_create_handle(socket_t *sock)
{
	int hdl = -1;

	if (sock->handle != -1)
		return (true);
	if (sock->type == TCP)
		hdl = socket(PF_INET, SOCK_STREAM, 0);
	else if (sock->type == UDP)
		hdl = socket(PF_INET, SOCK_DGRAM, 0);
	if (hdl == -1) {
		ERR("failed to create socket handle");
		return (false);
	}
	return (socket_create_from_handle(sock, hdl));
}

bool socket_create_from_handle(socket_t *sock, int handle)
{
	int y = 1;
	int r = 0;

	sock->handle = handle;
	socket_set_blocking(sock, sock->blocking);
	if (sock->type == TCP) {
		r = setsockopt(sock->handle, IPPROTO_TCP, TCP_NODELAY,
			&y, sizeof(y));
		if (r == -1) {
			ERR("failed to set socket option \"TCP_NODELAY\"");
			ERR("all your TCP packets will be buffered");
		}
	}
	else if (sock->type == UDP) {
		r = setsockopt(sock->handle, SOL_SOCKET, SO_BROADCAST,
			&y, sizeof(y));
		if (r == -1)
			ERR("failed to enable broadcast on UDP socket");
	}
	return (true);
}

void socket_destroy(socket_t *sock)
{
	if (sock->handle != -1)
		close(sock->handle);
	free(sock);
}