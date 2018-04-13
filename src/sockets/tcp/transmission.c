/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / transmission.c
*/

#include "tcp_socket.h"

socket_status_t tcp_socket_send(tcp_socket_t *sock,
	const void *data, size_t size)
{
	size_t sent;

	if (!sock->blocking)
		ERR("Warning: Partial sends might fail.");
	return tcp_socket_send_partial(sock, data, size, &sent);
}

socket_status_t tcp_socket_send_partial(tcp_socket_t *sock,
	const void *data, size_t size, size_t *sent)
{
	int result = 0;
	socket_status_t s;

	if (!data || (size == 0)) {
		ERR("No data to send");
		return (SOCKET_ERROR);
	}
	for (*sent = 0; *sent < size; *sent += result) {
		result = SEND(sock->handle, (const char *)data + *sent,
			size - *sent);
		if (result >= 0)
			continue;
		s = tcp_socket_get_error_status();
		if ((s == SOCKET_NOT_READY) && *sent != 0)
			return (SOCKET_PARTIAL);
		return (s);
	}
	return (SOCKET_DONE);
}

socket_status_t tcp_socket_receive(tcp_socket_t *sock,
	void *data, size_t size, size_t *received)
{
	int size_recv = 0;

	if (!data) {
		ERR("Cannot receive data: invalid buffer");
		return (SOCKET_ERROR);
	}
	if (received)
		*received = 0;
	size_recv = RECV(sock->handle, data, size);
	if (size_recv > 0) {
		if (received)
			*received = (size_t)size_recv;
		return (SOCKET_DONE);
	}
	else if (size_recv == 0)
		return (SOCKET_DISCONNECTED);
	return (tcp_socket_get_error_status());
}