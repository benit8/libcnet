/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / connection.c
*/

#include "tcp_socket.h"

static socket_status_t wait_for_socket(tcp_socket_t *sock, int timeout)
{
	fd_set selector;
	struct timeval time = {timeout, timeout * 1000000};

	FD_ZERO(&selector);
	FD_SET(sock->handle, &selector);
	if (select(sock->handle + 1, NULL, &selector, NULL, &time) > 0) {
		if (tcp_socket_get_remote_address(sock) != IP_NONE)
			return (SOCKET_DONE);
	}
	return (socket_get_error_status());
}

static socket_status_t connect_timeout(tcp_socket_t *sock,
	struct sockaddr_in adr, int timeout)
{
	int r = 0;
	socket_status_t s;
	bool blocking = sock->blocking;

	if (blocking)
		tcp_socket_set_blocking(sock, false);
	r = connect(sock->handle, (struct sockaddr *)&adr, sizeof(adr));
	if (r >= 0) {
		tcp_socket_set_blocking(sock, blocking);
		return (SOCKET_DONE);
	}
	s = socket_get_error_status();
	if (!blocking)
		return (s);
	if (s == SOCKET_NOT_READY)
		s = wait_for_socket(sock, timeout);
	tcp_socket_set_blocking(sock, true);
	return (s);
}

socket_status_t tcp_socket_connect(tcp_socket_t *sock, ip_address_t address,
	unsigned short port, int timeout)
{
	struct sockaddr_in adr;
	int r = 0;

	if (!tcp_socket_create_handle(sock))
		return (SOCKET_ERROR);
	bzero(&adr, sizeof(struct sockaddr_in));
	adr.sin_addr.s_addr = address;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	if (timeout <= 0) {
		r = connect(sock->handle, (struct sockaddr *)&adr, sizeof(adr));
		return (r >= 0 ? SOCKET_DONE : socket_get_error_status());
	}
	return (connect_timeout(sock, adr, timeout));
}

void tcp_socket_disconnect(tcp_socket_t *sock)
{
	if (sock->handle > 0) {
		close(sock->handle);
		sock->handle = -1;
	}
}