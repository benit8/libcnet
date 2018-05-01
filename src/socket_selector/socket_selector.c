/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector / socket_selector.c
*/

#include "cnet/socket_selector.h"

socket_selector_t *socket_selector_create(void)
{
	socket_selector_t *selector = calloc(1, sizeof(socket_selector_t));

	if (!selector)
		return (NULL);
	socket_selector_clear(selector);
	return (selector);
}

void socket_selector_destroy(socket_selector_t *selector)
{
	free(selector);
}