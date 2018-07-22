/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector / is_ready.c
*/

#include "cnet/socket_selector.h"

static bool socket_selector_is_fd_ready(const socket_selector_t *sel, int fd)
{
	if (fd == -1 || fd >= FD_SETSIZE)
		return (false);
	return (FD_ISSET(fd, &sel->sockets_ready) != 0);
}

bool socket_selector_is_socket_ready(const socket_selector_t *selector,
	socket_t *socket)
{
	return (socket_selector_is_fd_ready(selector, socket->handle));
}

bool socket_selector_is_tcp_socket_ready(const socket_selector_t *selector,
	tcp_socket_t *socket)
{
	return (socket_selector_is_fd_ready(selector, socket->handle));
}

bool socket_selector_is_tcp_listener_ready(const socket_selector_t *selector,
	tcp_listener_t *socket)
{
	return (socket_selector_is_fd_ready(selector, socket->handle));
}