/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / blocking.c
*/

#include "cnet/tcp_listener.h"

void tcp_listener_set_blocking(tcp_listener_t *list, bool blocking)
{
	socket_set_blocking((socket_t *)list, blocking);
}

bool tcp_listener_is_blocking(tcp_listener_t *list)
{
	return (list->blocking);
}