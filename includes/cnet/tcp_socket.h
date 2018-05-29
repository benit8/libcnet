/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tcp_socket.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "socket.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_TCP_SOCKET

////////////////////////////////////////////////////////////////////////////////

#define TCP_REMOTE_STR(s) ip_address_to_string(tcp_socket_get_remote_address(s))

////////////////////////////////////////////////////////////////////////////////

typedef socket_t tcp_socket_t;

////////////////////////////////////////////////////////////////////////////////

// Creates an uninitialized socket
tcp_socket_t *tcp_socket_bare(void);

// Creates the socket handle
bool tcp_socket_create_handle(tcp_socket_t *sock);

// Creates the socket from an existing handle
bool tcp_socket_create_from_handle(tcp_socket_t *sock, int handle);

// Creates and initialize a socket
tcp_socket_t *tcp_socket_create(void);

// Destroys a socket
void tcp_socket_destroy(tcp_socket_t *sock);


// Connects the socket to a peer
socket_status_t tcp_socket_connect(tcp_socket_t *sock, ip_address_t address,
	unsigned short port, int timeout);

// Disconnect the socket from its peer
void tcp_socket_disconnect(tcp_socket_t *sock);

// Sends data over a socket and gets the number of bytes sent
socket_status_t tcp_socket_send(tcp_socket_t *sock,
	const void *data, size_t size, size_t *sent);

// Receives data over a socket
socket_status_t tcp_socket_receive(tcp_socket_t *sock,
	void *data, size_t size, size_t *received);

// Gets the local port
unsigned short tcp_socket_get_local_port(tcp_socket_t *sock);

// Gets the peer's address
ip_address_t tcp_socket_get_remote_address(tcp_socket_t *sock);

// Gets the peer's port
unsigned short tcp_socket_get_remote_port(tcp_socket_t *sock);

// Sets/gets the blocking state of the socket
void tcp_socket_set_blocking(tcp_socket_t *sock, bool blocking);
bool tcp_socket_is_blocking(tcp_socket_t *sock);