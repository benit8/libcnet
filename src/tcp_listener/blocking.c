/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / blocking.c
*/

#include "tcp_listener.h"

void tcp_listener_set_blocking(tcp_listener_t *list, bool blocking)
{
	int status;

	if (list->handle == -1)
		return;
	status = fcntl(list->handle, F_GETFL);
	if (blocking) {
		if (fcntl(list->handle, F_SETFL, status & ~O_NONBLOCK) == -1)
			ERR("failed to block listener: %s", strerror(errno));
	}
	else {
		if (fcntl(list->handle, F_SETFL, status | O_NONBLOCK) == -1)
			ERR("failed to unblock listener: %s", strerror(errno));
	}
	list->blocking = blocking;
}

bool tcp_listener_is_blocking(tcp_listener_t *list)
{
	return (list->blocking);
}