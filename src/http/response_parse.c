/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / response_parse.c
*/

#include "cnet/http.h"

static void fignore(FILE *stream, size_t n, int delim)
{
	for (size_t i = 0; i < n; ++i) {
		if (fgetc(stream) == delim)
			break;
	}
}

static bool parse_version(http_response_t *res, FILE *in)
{
	char *line = NULL;
	size_t size = 0;
	char *p = NULL;

	if (getline(&line, &size, in) > 7) {
		if (strncasecmp(line, "http/", 5) != 0) {
			free(line);
			return (false);
		}
		res->major_version = strtoul(line + 5, &p, 10);
		res->minor_version = strtoul(p + 1, &p, 10);
		res->status = strtol(p + 1, &p, 10);
		free(line);
		return (true);
	}
	free(line);
	return (false);
}

static void parse_fields(http_response_t *res, FILE *in)
{
	char *line = NULL;
	size_t size = 0;
	char *p = NULL;
	size_t s = 0;

	while (getline(&line, &size, in) > 2) {
		p = strstr(line, ": ");
		if (!p)
			continue;
		*p = '\0';
		p += 2;
		s = strlen(p);
		if (s > 0 && p[s - 1] == '\r')
			p[s - 1] = '\0';
		http_response_set_field(res, line, p);
	}
	free(line);
}

static void read_body(http_response_t *res, FILE *in)
{
	size_t length = 0;
	size_t size = 0;
	size_t bsize = 0;
	char *line = NULL;
	FILE *body = open_memstream(&res->body, &bsize);

	while (getline(&line, &size, in) > 0) {
		length = strtoul(line, NULL, 16);
		fignore(in, SIZE_MAX, '\n');
		for (size_t i = 0; i < length; ++i)
			fputc(fgetc(in), body);
		fignore(in, SIZE_MAX, '\n');
	}
	free(line);
	fclose(body);
}

void http_response_parse(http_response_t *response, char *data, size_t len)
{
	FILE *in = fmemopen(data, len, "r");

	if (!in)
		return;
	if (!parse_version(response, in)) {
		response->status = HTTP_INVALID_RESPONSE;
		fclose(in);
		return;
	}
	fignore(in, SIZE_MAX, '\n');
	parse_fields(response, in);
	if (strcasecmp(http_response_get_field(response, "transfer-content"),
		"chunked") != 0)
		response->body = strdup(data + ftell(in));
	else
		read_body(response, in);
	if (response->body[strlen(response->body) - 1] == '\n')
		response->body[strlen(response->body) - 1] = '\0';
	parse_fields(response, in);
	fclose(in);
}