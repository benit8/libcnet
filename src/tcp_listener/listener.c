/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / listener.c
*/

#include "tcp_listener.h"

tcp_listener_t *tcp_listener_bare(void)
{
	tcp_listener_t *list = calloc(1, sizeof(tcp_listener_t));

	if (!list) {
		ERR("out of memory");
		return (NULL);
	}
	list->handle = -1;
	list->blocking = true;
	return (list);
}

bool tcp_listener_create_handle(tcp_listener_t *list)
{
	int handle = -1;

	if (list->handle != -1)
		return (true);
	handle = socket(PF_INET, SOCK_STREAM, 0);
	if (handle == -1) {
		ERR("failed to create listener handle");
		return (false);
	}
	return (tcp_listener_create_from_handle(list, handle));
}

bool tcp_listener_create_from_handle(tcp_listener_t *list, int handle)
{
	int y = 1;
	int r = 0;

	list->handle = handle;
	tcp_listener_set_blocking(list, list->blocking);
	r = setsockopt(list->handle, IPPROTO_TCP, TCP_NODELAY, &y, sizeof(y));
	if (r == -1) {
		ERR("failed to set listener option 'TCP_NODELAY'."
			"TCP packets will be buffered");
	}
	return (true);
}

tcp_listener_t *tcp_listener_create(void)
{
	tcp_listener_t *list = tcp_listener_bare();

	if (!list)
		return (NULL);
	if (!tcp_listener_create_handle(list)) {
		free(list);
		return (NULL);
	}
	return (list);
}

void tcp_listener_destroy(tcp_listener_t *list)
{
	tcp_listener_close(list);
	free(list);
}