/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / listener.c
*/

#include "tcp_listener.h"

tcp_listener_t *tcp_listener_bare(void)
{
	return ((tcp_listener_t *)socket_bare(TCP));
}

bool tcp_listener_create_handle(tcp_listener_t *list)
{
	return (socket_create_handle((socket_t *)list));
}

bool tcp_listener_create_from_handle(tcp_listener_t *list, int handle)
{
	return (socket_create_from_handle((socket_t *)list, handle));
}

tcp_listener_t *tcp_listener_create(void)
{
	return ((tcp_listener_t *)socket_create(TCP));
}

void tcp_listener_destroy(tcp_listener_t *list)
{
	tcp_listener_close(list);
	socket_destroy((socket_t *)list);
}