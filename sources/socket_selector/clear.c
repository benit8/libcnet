/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector / clear.c
*/

#include "cnet/socket_selector.h"

void socket_selector_clear(socket_selector_t *selector)
{
	FD_ZERO(&selector->all_sockets);
	FD_ZERO(&selector->sockets_ready);
	selector->max_socket = 0;
}