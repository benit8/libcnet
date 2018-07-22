/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_selector.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "tcp_listener.h"
#include "tcp_socket.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_SOCKET_SELECTOR

////////////////////////////////////////////////////////////////////////////////

typedef struct socket_selector
{
	fd_set all_sockets;
	fd_set sockets_ready;
	int max_socket;
} socket_selector_t;

////////////////////////////////////////////////////////////////////////////////

socket_selector_t *socket_selector_create(void);
void socket_selector_destroy(socket_selector_t *selector);

void socket_selector_clear(socket_selector_t *selector);
bool socket_selector_wait(socket_selector_t *selector, int timeout);

void socket_selector_add_socket(socket_selector_t *selector,
	socket_t *socket);
void socket_selector_add_tcp_socket(socket_selector_t *selector,
	tcp_socket_t *socket);
void socket_selector_add_tcp_listener(socket_selector_t *selector,
	tcp_listener_t *socket);

void socket_selector_remove_socket(socket_selector_t *selector,
	socket_t *socket);
void socket_selector_remove_tcp_socket(socket_selector_t *selector,
	tcp_socket_t *socket);
void socket_selector_remove_tcp_listener(socket_selector_t *selector,
	tcp_listener_t *socket);

bool socket_selector_is_socket_ready(const socket_selector_t *selector,
	socket_t *socket);
bool socket_selector_is_tcp_socket_ready(const socket_selector_t *selector,
	tcp_socket_t *socket);
bool socket_selector_is_tcp_listener_ready(const socket_selector_t *selector,
	tcp_listener_t *socket);