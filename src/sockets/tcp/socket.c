/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / socket.c
*/

#include "tcp_socket.h"

tcp_socket_t *tcp_socket_bare(void)
{
	tcp_socket_t *sock = calloc(1, sizeof(tcp_socket_t));

	if (!sock) {
		ERR("out of memory");
		return (NULL);
	}
	sock->handle = -1;
	sock->blocking = true;
	return (sock);
}

bool tcp_socket_create_handle(tcp_socket_t *sock)
{
	int handle = -1;

	if (sock->handle != -1)
		return (true);
	handle = socket(PF_INET, SOCK_STREAM, 0);
	if (handle == -1) {
		ERR("failed to create socket handle");
		return (false);
	}
	return (tcp_socket_create_from_handle(sock, handle));
}

bool tcp_socket_create_from_handle(tcp_socket_t *sock, int handle)
{
	int y = 1;
	int r = 0;

	sock->handle = handle;
	tcp_socket_set_blocking(sock, sock->blocking);
	r = setsockopt(sock->handle, IPPROTO_TCP, TCP_NODELAY, &y, sizeof(y));
	if (r == -1) {
		ERR("failed to set socket option 'TCP_NODELAY'. TCP packets \
			will be buffered");
	}
	return (true);
}

tcp_socket_t *tcp_socket_create(void)
{
	tcp_socket_t *sock = tcp_socket_bare();

	if (!sock)
		return (NULL);
	if (!tcp_socket_create_handle(sock)) {
		free(sock);
		return (NULL);
	}
	return (sock);
}

void tcp_socket_destroy(tcp_socket_t *sock)
{
	tcp_socket_disconnect(sock);
	free(sock);
}