/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / response_fields.c
*/

#include "cnet/http.h"

void http_response_set_field(http_response_t *response, const char *field,
	const char *value)
{
	http_field_t *fields = NULL;

	if (!field)
		return;
	fields = realloc(response->field_table,
		(response->field_count + 1) * sizeof(http_field_t));
	if (!fields) {
		ERR("could not add field: out of memory");
		return;
	}
	fields[response->field_count].name = strdup(field);
	fields[response->field_count].value = strdup(value ? value : "");
	response->field_table = fields;
	response->field_count++;
}

bool http_response_has_field(http_response_t *response, const char *field)
{
	for (size_t i = 0; i < response->field_count; ++i) {
		if (strcasecmp(field, response->field_table[i].name) == 0)
			return (true);
	}
	return (false);
}

char *http_response_get_field(http_response_t *res, const char *f)
{
	for (size_t i = 0; i < res->field_count; ++i) {
		if (strcasecmp(f, res->field_table[i].name) == 0)
			return (res->field_table[i].value);
	}
	return ("");
}