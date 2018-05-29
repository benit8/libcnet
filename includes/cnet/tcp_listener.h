/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_listener.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "tcp_socket.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_TCP_LISTENER

////////////////////////////////////////////////////////////////////////////////

typedef tcp_socket_t tcp_listener_t;

////////////////////////////////////////////////////////////////////////////////

// Creates an uninitialized socket
tcp_listener_t *tcp_listener_bare(void);

// Creates the listener handle
bool tcp_listener_create_handle(tcp_listener_t *listener);

// Creates the listener from an existing handle
bool tcp_listener_create_from_handle(tcp_listener_t *listener, int handle);

// Creates and initialize a listener
tcp_listener_t *tcp_listener_create(void);

// Destroys a listener
void tcp_listener_destroy(tcp_listener_t *listener);

// Start listening for connections
socket_status_t tcp_listener_listen(tcp_listener_t *listener,
	unsigned short port, ip_address_t address);

// Accept a new connection
socket_status_t tcp_listener_accept(tcp_listener_t *listener,
	tcp_socket_t **connected);

// Stop listening and close the socket
void tcp_listener_close(tcp_listener_t *listener);

// Sets/gets the blocking state of the socket
void tcp_listener_set_blocking(tcp_listener_t *listener, bool blocking);
bool tcp_listener_is_blocking(tcp_listener_t *listener);

// Gets the local port
unsigned short tcp_listener_get_local_port(tcp_listener_t *listener);

// Gets the listened address
ip_address_t tcp_listener_get_local_address(tcp_listener_t *list);