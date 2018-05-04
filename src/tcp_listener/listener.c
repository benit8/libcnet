/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / listener.c
*/

#include "cnet/tcp_listener.h"

tcp_listener_t *tcp_listener_bare(void)
{
	return ((tcp_listener_t *)tcp_socket_bare());
}

tcp_listener_t *tcp_listener_create(void)
{
	return ((tcp_listener_t *)tcp_socket_create());
}

bool tcp_listener_create_handle(tcp_listener_t *listener)
{
	return (tcp_socket_create_handle((tcp_socket_t *)listener));
}

bool tcp_listener_create_from_handle(tcp_listener_t *listener, int handle)
{
	return (tcp_socket_create_from_handle((tcp_socket_t *)listener, handle));
}

void tcp_listener_destroy(tcp_listener_t *listener)
{
	tcp_listener_close(listener);
	tcp_socket_destroy((tcp_socket_t *)listener);
}