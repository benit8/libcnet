/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / local.c
*/

#include "cnet/tcp_listener.h"

static struct sockaddr_in *tcp_listener_get_local_infos(tcp_listener_t *list)
{
	static struct sockaddr_in address;
	socklen_t size = sizeof(address);

	if (list->handle == -1)
		return (NULL);
	if (getsockname(list->handle, (struct sockaddr *)&address, &size) != -1)
		return (&address);
	return (NULL);
}

unsigned short tcp_listener_get_local_port(tcp_listener_t *list)
{
	struct sockaddr_in *address = tcp_listener_get_local_infos(list);

	return (address ? ntohs(address->sin_port) : 0);
}

ip_address_t tcp_listener_get_local_address(tcp_listener_t *list)
{
	struct sockaddr_in *address = tcp_listener_get_local_infos(list);

	return (address ? address->sin_addr.s_addr : IP_NONE);
}