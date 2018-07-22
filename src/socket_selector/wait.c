/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector / wait.c
*/

#include "cnet/socket_selector.h"

bool socket_selector_wait(socket_selector_t *selector, int timeout)
{
	struct timeval time;
	int count;

	time.tv_sec = (long)(timeout);
	time.tv_usec = (long)(timeout * 1000000);
	selector->sockets_ready = selector->all_sockets;
	count = select(selector->max_socket + 1, &selector->sockets_ready,
		NULL, NULL, timeout != 0 ? &time : NULL);
	return (count > 0);
}