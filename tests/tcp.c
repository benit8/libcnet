/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tests / tcp_sockets.c
*/

#include <ctype.h>
#include <stdio.h>
#include "tcp_listener.h"
#include "tcp_socket.h"

////////////////////////////////////////////////////////////////////////////////

#define UNUSED __attribute__((unused))

#define DIE(msg, ...) \
	do { \
		fprintf(stderr, "%s: " msg "\n", __func__, ##__VA_ARGS__); \
		exit(1); \
	} while (0)

////////////////////////////////////////////////////////////////////////////////

const unsigned short PORT = 8182;

////////////////////////////////////////////////////////////////////////////////

char *read_input(void)
{
	size_t n = 0;
	char *input = NULL;

	ssize_t r = getline(&input, &n, stdin);
	if (r == -1)
		return (NULL);
	input[r - 1] = '\0';
	return (input);
}

char *prompt_input(void)
{
	char *input = NULL;

	do {
		printf("Please enter a message: ");
		input = read_input();
	} while (!input || strlen(input) == 0);
	return (input);
}

////////////////////////////////////////////////////////////////////////////////

void server()
{
	// Create the listener
	tcp_listener_t *listener = tcp_listener_create();
	if (!listener || listener->handle == -1)
		DIE("Listener creation failed");

	// Listen to a specific port
	if (tcp_listener_listen(listener, PORT, IP_ANY) != SOCKET_DONE)
		DIE("Could not listen to port %hu", PORT);
	printf("Listening to port %hu, waiting for connection...\n", PORT);

	// Accept entering connection
	tcp_socket_t *socket = NULL;
	if (tcp_listener_accept(listener, &socket) != SOCKET_DONE)
		return;
	printf("Client connected: %s\n", ip_address_to_string(tcp_socket_get_remote_address(socket)));

	// Send message to client
	const char out[] = "Hi, welcome to the server";
	if (tcp_socket_send(socket, out, sizeof(out)) != SOCKET_DONE)
		return;
	printf("Message to the client: \"%s\" (%lu)\n", out, sizeof(out));

	// Receive message from client
	char in[128];
	size_t received;
	if (tcp_socket_receive(socket, in, sizeof(in), &received) != SOCKET_DONE)
		return;
	printf("Message from the client: \"%s\" (%lu)\n", in, received);

	// Destroy client & listener
	tcp_socket_destroy(socket);
	tcp_listener_destroy(listener);
}

////////////////////////////////////////////////////////////////////////////////

void client()
{
	// Create the socket
	tcp_socket_t *socket = tcp_socket_create();
	if (!socket || socket->handle == -1)
		DIE("Socket creation failed");

	printf("type: %d\n", socket->type);
	printf("handle: %d\n", socket->handle);
	printf("blocking: %s\n", socket->blocking ? "true" : "false");

	// Connect the socket
	if (tcp_socket_connect(socket, IP_LOCALHOST, PORT, 0) != SOCKET_DONE)
		DIE("Could not connect to server");

	// Receive data from the server
	char in[128];
	size_t received;
	if (tcp_socket_receive(socket, in, sizeof(in), &received) != SOCKET_DONE)
		return;
	printf("Message from the server: \"%s\" (%lu)\n", in, received);

	// Send input data to the server
	char *out = prompt_input();
	if (tcp_socket_send(socket, out, strlen(out)) != SOCKET_DONE)
		return;
	printf("Message to the server: \"%s\" (%lu)\n", out, strlen(out));
	free(out);

	// Destroy the socket
	tcp_socket_destroy(socket);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv UNUSED)
{
	if (argc < 2)
		client();
	else
		server();

	return (0);
}