/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / request.c
*/

#include "cnet/http.h"

http_request_t *http_request_create(const char *uri, http_method_t method,
	const char *body)
{
	http_request_t *request = calloc(1, sizeof(http_request_t));

	if (!request)
		return (NULL);
	http_request_set_body(request, body);
	http_request_set_uri(request, uri);
	http_request_set_method(request, method);
	request->field_table = NULL;
	request->field_count = 0;
	http_request_set_http_version(request, 1, 1);
	return (request);
}

static void destroy_field_table(http_request_t *request)
{
	for (size_t i = 0; i < request->field_count; ++i) {
		free(request->field_table[i].name);
		if (request->field_table[i].value)
			free(request->field_table[i].value);
	}
	free(request->field_table);
}

void http_request_destroy(http_request_t *request)
{
	if (request->body)
		free(request->body);
	if (request->uri)
		free(request->uri);
	if (request->field_table)
		destroy_field_table(request);
	free(request);
}

http_request_t *http_request_copy(http_request_t *src)
{
	http_request_t *copy = calloc(1, sizeof(http_request_t));

	if (!copy)
		return (NULL);
	http_request_set_body(copy, src->body);
	http_request_set_uri(copy, src->uri);
	http_request_set_method(copy, src->method);
	copy->field_count = src->field_count;
	copy->field_table = calloc(copy->field_count, sizeof(http_field_t));
	for (size_t i = 0; i < copy->field_count; ++i) {
		copy->field_table[i].name = strdup(src->field_table[i].name);
		copy->field_table[i].value = strdup(src->field_table[i].value);
	}
	copy->major_version = src->major_version;
	copy->minor_version = src->minor_version;
	return (copy);
}