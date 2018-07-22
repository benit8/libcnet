/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / impl / socket.c
*/

#include "cnet/socket.h"

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

bool socket_create_handle(socket_t *sock)
{
	int hdl = -1;

	if (sock->handle != -1)
		return (true);
	if (sock->type == SOCKET_TCP)
		hdl = socket(PF_INET, SOCK_STREAM, 0);
	else if (sock->type == SOCKET_UDP)
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
	int s = sizeof(y);

	sock->handle = handle;
	socket_set_blocking(sock, sock->blocking);
	if (sock->type == SOCKET_TCP &&
		setsockopt(sock->handle, IPPROTO_TCP, TCP_NODELAY, &y, s) < 0) {
		ERR("failed to set socket option \"TCP_NODELAY\"");
		ERR("all your TCP packets will be buffered");
	}
	else if (sock->type == SOCKET_UDP &&
		setsockopt(sock->handle, SOL_SOCKET, SO_BROADCAST, &y, s) < 0) {
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