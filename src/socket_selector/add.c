/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector / add.c
*/

#include "cnet/socket_selector.h"

static void socket_selector_add_fd(socket_selector_t *selector, int fd)
{
	if (fd == -1)
		return;
	else if (fd >= FD_SETSIZE) {
		ERR("could not add socket to listener: FD is too high. \
			See FD_SETISZE setting");
		return;
	}
	if (fd > selector->max_socket)
		selector->max_socket = fd;
	FD_SET(fd, &selector->all_sockets);
}

#ifdef CNET_SOCKET
void socket_selector_add_socket(socket_selector_t *selector,
	socket_t *socket)
{
	socket_selector_add_fd(selector, socket->handle);
}
#endif

#ifdef CNET_TCP_SOCKET
void socket_selector_add_tcp_socket(socket_selector_t *selector,
	tcp_socket_t *socket)
{
	socket_selector_add_fd(selector, socket->handle);
}
#endif

#ifdef CNET_TCP_LISTENER
void socket_selector_add_tcp_listener(socket_selector_t *selector,
	tcp_listener_t *listener)
{
	socket_selector_add_fd(selector, listener->handle);
}
#endif

#ifdef CNET_UDP_SOCKET
void socket_selector_add_udp_socket(socket_selector_t *selector,
	udp_socket_t *socket)
{
	socket_selector_add_fd(selector, socket->handle);
}
#endif