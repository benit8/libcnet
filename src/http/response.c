/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http / response.c
*/

#include "cnet/http.h"

http_response_t *http_response_create(void)
{
	http_response_t *response = calloc(1, sizeof(http_response_t));

	if (!response)
		return (NULL);
	response->body = NULL;
	response->status = HTTP_CONNECTION_FAILED;
	response->field_table = NULL;
	response->field_count = 0;
	response->major_version = 0;
	response->minor_version = 0;
	return (response);
}

static void destroy_field_table(http_response_t *response)
{
	for (size_t i = 0; i < response->field_count; ++i) {
		free(response->field_table[i].name);
		if (response->field_table[i].value)
			free(response->field_table[i].value);
	}
	free(response->field_table);
}

void http_response_destroy(http_response_t *response)
{
	if (response->body)
		free(response->body);
	if (response->field_table)
		destroy_field_table(response);
	free(response);
}