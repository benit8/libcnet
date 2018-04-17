/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** sockets / impl / error.c
*/

#include "socket.h"

socket_status_t socket_get_error_status(void)
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

char *socket_status_to_string(socket_status_t status)
{
	switch (status) {
		case SOCKET_DONE:
			return "Done";
		case SOCKET_NOT_READY:
			return "Not ready";
		case SOCKET_PARTIAL:
			return "Partial";
		case SOCKET_DISCONNECTED:
			return "Disconnected";
		default:
			return "Error";
	}
}