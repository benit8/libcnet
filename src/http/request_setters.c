/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / request_setters.c
*/

#include "cnet/http.h"

void http_request_set_method(http_request_t *request, http_method_t method)
{
	request->method = method;
}

void http_request_set_uri(http_request_t *request, const char *uri)
{
	if (request->uri)
		free(request->uri);
	if (!uri) {
		request->uri = NULL;
		return;
	}
	asprintf(&request->uri, "%s%s", uri[0] == '/' ? "" : "/", uri);
}

void http_request_set_http_version(http_request_t *req, unsigned int major,
	unsigned int minor)
{
	req->major_version = major;
	req->minor_version = minor;
}

void http_request_set_body(http_request_t *request, const char *body)
{
	if (!body)
		body = "";
	if (request->body)
		free(request->body);
	request->body = body ? strdup(body) : NULL;
}