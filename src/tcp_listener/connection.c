/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener / connection.c
*/

#include "cnet/tcp_listener.h"

socket_status_t tcp_listener_listen(tcp_listener_t *list,
	unsigned short port, ip_address_t address)
{
	struct sockaddr_in addr;

	if (!tcp_listener_create_handle(list))
		return (SOCKET_ERROR);
	if (address == IP_NONE || address == IP_BROADCAST)
		return (SOCKET_ERROR);
	bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_addr.s_addr = address;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (bind(list->handle, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		ERR("failed to bind listener socket to port %hu", port);
		return (SOCKET_ERROR);
	}
	if (listen(list->handle, SOMAXCONN) == -1) {
		ERR("failed to listen to port %hu", port);
		return (SOCKET_ERROR);
	}
	return (SOCKET_DONE);
}

static socket_status_t accept_soc(tcp_listener_t *list, tcp_socket_t *connected)
{
	struct sockaddr_in addr;
	socklen_t size = sizeof(addr);

	if (list->handle == -1) {
		ERR("Cannot accept connection: socket not listening");
		return (SOCKET_ERROR);
	}
	int remote = accept(list->handle, (struct sockaddr *)&addr, &size);
	if (remote == -1)
		return (socket_get_error_status());
	tcp_socket_disconnect(connected);
	tcp_socket_create_from_handle(connected, remote);
	return (SOCKET_DONE);
}

socket_status_t tcp_listener_accept(tcp_listener_t *list,
	tcp_socket_t **connected)
{
	socket_status_t status;

	if (!*connected)
		*connected = tcp_socket_bare();
	status = accept_soc(list, *connected);
	if (status != SOCKET_DONE) {
		tcp_socket_destroy(*connected);
		*connected = NULL;
	}
	return (status);
}

void tcp_listener_close(tcp_listener_t *list)
{
	if (list->handle != -1) {
		close(list->handle);
		list->handle = -1;
	}
}