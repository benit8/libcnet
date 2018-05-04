/*
** EPITECH PROJECT, 2018
** http
** File description:
** http / http_request.c
*/

#include "cnet/http.h"

static void set_mandatory_fields(http_t *http, http_request_t *req)
{
	char buffer[64];

	if (!http_request_has_field(req, "User-Agent"))
		http_request_set_field(req, "User-Agent", "libcnet/1.0");
	if (!http_request_has_field(req, "Host"))
		http_request_set_field(req, "Host", http->host_name);
	if (req->method == HTTP_POST &&
		!http_request_has_field(req, "Content-Type"))
		http_request_set_field(req, "Content-Type",
			"application/x-www-form-urlencoded");
	if (!http_request_has_field(req, "Content-Length")) {
		bzero(buffer, sizeof(buffer));
		snprintf(buffer, sizeof(buffer), "%lu", strlen(req->body));
		http_request_set_field(req, "Content-Length", buffer);
	}
	if ((req->major_version * 10 + req->minor_version >= 11) &&
		!http_request_has_field(req, "Connection"))
		http_request_set_field(req, "Connection", "close");
}

static void http_receive_response(http_t *http, http_response_t *response)
{
	char *received_str = NULL;
	size_t received_size = 0;
	char b[1024];
	size_t size = 0;
	FILE *stream = open_memstream(&received_str, &received_size);

	if (!stream) {
		ERR("could not receive response");
		return;
	}
	while (tcp_socket_receive(http->connection, b, sizeof(b),
		&size) == SOCKET_DONE)
		fwrite(b, sizeof(char), size, stream);
	fclose(stream);
	http_response_parse(response, received_str, received_size);
	free(received_str);
}

static void http_init_connection(http_t *http, http_request_t *request,
	http_response_t *response, int t)
{
	char *reqstr = NULL;
	socket_status_t s;

	s = tcp_socket_connect(http->connection, http->host, http->port, t);
	if (s != SOCKET_DONE) {
		ERR("connection to host failed");
		return;
	}
	reqstr = http_request_prepare(request);
	s = tcp_socket_send(http->connection, reqstr, strlen(reqstr), NULL);
	free(reqstr);
	if (s == SOCKET_DONE)
		http_receive_response(http, response);
	tcp_socket_disconnect(http->connection);
}

http_response_t *http_send_request(http_t *http, http_request_t *request, int t)
{
	http_request_t *to_send = http_request_copy(request);
	http_response_t *response = NULL;

	if (!http || !to_send)
		return (NULL);
	set_mandatory_fields(http, to_send);
	response = http_response_create();
	if (!response) {
		http_request_destroy(to_send);
		return (NULL);
	}
	http_init_connection(http, to_send, response, t);
	http_request_destroy(to_send);
	return (response);
}