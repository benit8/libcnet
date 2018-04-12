/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / tcp / error.c
*/

#include "tcp_socket.h"

socket_status_t tcp_socket_get_error_status(void)
{
	if (errno == EAGAIN || errno == EINPROGRESS)
		return (SOCKET_NOT_READY);
	switch (errno) {
		case EWOULDBLOCK:
			return SOCKET_NOT_READY;
		case ECONNABORTED:
		case ECONNRESET:
		case ETIMEDOUT:
		case ENETRESET:
		case ENOTCONN:
		case EPIPE:
			return SOCKET_DISCONNECTED;
		default:
			return SOCKET_ERROR;
	}
}