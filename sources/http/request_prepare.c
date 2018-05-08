/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / request_prepare.c
*/

#include "cnet/http.h"

char *http_request_prepare(const http_request_t *r)
{
	char *out = NULL;
	size_t out_size = 0;
	FILE *stream = open_memstream(&out, &out_size);

	if (!stream) {
		ERR("could not prepare request: %s", strerror(errno));
		return (NULL);
	}
	fprintf(stream, "%s ", http_method_to_string(r->method));
	fprintf(stream, "%s ", r->uri);
	fprintf(stream, "HTTP/%u.%u\r\n", r->major_version, r->minor_version);
	for (size_t i = 0; i < r->field_count; ++i) {
		fprintf(stream, "%s: %s\r\n", r->field_table[i].name,
			r->field_table[i].value ? r->field_table[i].value : "");
	}
	fprintf(stream, "\r\n%s\r\n", r->body);
	fflush(stream);
	fclose(stream);
	return (out);
}