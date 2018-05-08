/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / http.c
*/

#include "cnet/http.h"

http_t *http_create(const char *host, unsigned short port)
{
	http_t *http = calloc(1, sizeof(http_t));

	if (!http)
		return (NULL);
	http->connection = tcp_socket_bare();
	if (!http->connection) {
		ERR("could not create connection interface: out of memory");
		free(http);
		return (NULL);
	}
	http_set_host(http, host, port);
	return (http);
}

void http_destroy(http_t *http)
{
	tcp_socket_destroy(http->connection);
	if (http->host_name)
		free(http->host_name);
	free(http);
}

static void set_host_name(char **hostp, const char *new_host)
{
	if (*hostp)
		free(*hostp);
	*hostp = new_host ? strdup(new_host) : NULL;
}

void http_set_host(http_t *http, const char *host, unsigned short port)
{
	if (!http || !host)
		return;
	if (strncasecmp(host, "http://", 7) == 0) {
		set_host_name(&http->host_name, host + 7);
		http->port = port != 0 ? port : 80;
	}
	else if (strncasecmp(host, "https://", 8) == 0) {
		ERR("HTTPS protocol is not supported.");
		set_host_name(&http->host_name, NULL);
		http->port = 0;
	}
	else {
		set_host_name(&http->host_name, host);
		http->port = port != 0 ? port : 80;
	}
	if (http->host_name[strlen(http->host_name) - 1] == '/')
		http->host_name[strlen(http->host_name) - 1] = '\0';
	http->host = ip_address_from_string(http->host_name);
}