/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "ip_address.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_SOCKET

////////////////////////////////////////////////////////////////////////////////

// #define EPITECH

#ifndef EPITECH
	#define SEND(f, d, s) (send(f, d, s, MSG_NOSIGNAL))
	#define RECV(f, d, s) (recv(f, (char *)d, (int)s, MSG_NOSIGNAL))
#else
	#define SEND(f, d, s) (write(f, d, s))
	#define RECV(f, d, s) (read(f, d, s))
#endif

////////////////////////////////////////////////////////////////////////////////

typedef enum socket_type
{
	TCP,
	UDP
} socket_type_t;

typedef enum socket_status
{
	SOCKET_DONE,
	SOCKET_NOT_READY,
	SOCKET_PARTIAL,
	SOCKET_DISCONNECTED,
	SOCKET_ERROR
} socket_status_t;

////////////////////////////////////////////////////////////////////////////////

typedef struct socket
{
	socket_type_t type;
	int handle;
	bool blocking;
} socket_t;

////////////////////////////////////////////////////////////////////////////////

// Creates and initialize a socket
socket_t *socket_create(socket_type_t type);

// Creates an uninitialized socket
socket_t *socket_bare(socket_type_t type);

// Creates the socket handle
bool socket_create_handle(socket_t *sock);

// Creates the socket from an existing handle
bool socket_create_from_handle(socket_t *sock, int handle);

// Destroys a socket
void socket_destroy(socket_t *sock);


// Sets the blocking state of the socket
void socket_set_blocking(socket_t *sock, bool blocking);

// Gets the blocking state of the socket
bool socket_is_blocking(socket_t *sock);


socket_status_t socket_get_error_status(void);
char *socket_status_to_string(socket_status_t status);