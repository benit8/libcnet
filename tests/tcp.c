/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tests / tcp_sockets.c
*/

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

const unsigned short PORT = 8181;

////////////////////////////////////////////////////////////////////////////////

char *read_input(void)
{
	size_t n = 0;
	char *input = NULL;

	ssize_t r = getline(&input, &n, stdin);
	if (r == -1)
		return (NULL);
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
	tcp_listener_t *listener = tcp_listener_create();
	if (!listener)
		DIE("Listener creation failed");

	if (tcp_listener_listen(listener, PORT, IP_ANY) != SOCKET_DONE)
		DIE("Could not listen to port %hu", PORT);
	printf("Listening to port %hu, waiting for connection...\n", PORT);

	tcp_socket_t *socket = NULL;
	if (tcp_listener_accept(listener, &socket) != SOCKET_DONE)
		return;
	printf("Client connected: %s\n", ip_address_to_string(tcp_socket_get_remote_address(socket)));

	const char out[] = "Hi, welcome to the server";
	if (tcp_socket_send(socket, out, sizeof(out)) != SOCKET_DONE)
		return;
	printf("Message to the client: \"%s\" (%lu)\n", out, sizeof(out));

	char in[128];
	size_t received;
	if (tcp_socket_receive(socket, in, sizeof(in), &received) != SOCKET_DONE)
		return;
	printf("Message from the client: \"%s\" (%lu)\n", in, received);

	tcp_socket_destroy(socket);
	tcp_listener_destroy(listener);
}

////////////////////////////////////////////////////////////////////////////////

void client()
{
	tcp_socket_t *socket = tcp_socket_create();
	if (!socket)
		DIE("Socket creation failed");

	if (tcp_socket_connect(socket, IP_LOCALHOST, PORT, 60) != SOCKET_DONE)
		DIE("Could not connect to server");

	char in[128];
	size_t received;
	if (tcp_socket_receive(socket, in, sizeof(in), &received) != SOCKET_DONE)
		return;
	printf("Message from the server: \"%s\" (%lu)\n", in, received);

	char *out = prompt_input();
	if (tcp_socket_send(socket, out, strlen(out)) != SOCKET_DONE)
		return;
	printf("Message to the server: \"%s\" (%lu)\n", out, sizeof(out));
	free(out);

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