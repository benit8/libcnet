/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / local.c
*/

#include "cnet/tcp_listener.h"

unsigned short tcp_listener_get_local_port(tcp_listener_t *list)
{
	struct sockaddr_in address;
	socklen_t size = sizeof(address);

	if (list->handle == -1)
		return (0);
	if (getsockname(list->handle, (struct sockaddr *)&address, &size) != -1)
		return (ntohs(address.sin_port));
	return (0);
}