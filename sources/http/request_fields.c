/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / request_fields.c
*/

#include "cnet/http.h"

void http_request_set_field(http_request_t *request, const char *field,
	const char *value)
{
	http_field_t *fields = NULL;

	if (!field)
		return;
	fields = realloc(request->field_table,
		(request->field_count + 1) * sizeof(http_field_t));
	if (!fields) {
		ERR("could not add field: out of memory");
		return;
	}
	fields[request->field_count].name = strdup(field);
	fields[request->field_count].value = strdup(value ? value : "");
	request->field_table = fields;
	request->field_count++;
}

bool http_request_has_field(http_request_t *request, const char *field)
{
	for (size_t i = 0; i < request->field_count; ++i) {
		if (strcasecmp(field, request->field_table[i].name) == 0)
			return (true);
	}
	return (false);
}