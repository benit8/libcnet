/*
** EPITECH PROJECT, 2018
** http
** File description:
** http / method.c
*/

#include "cnet/http.h"

static const char *http_method_names[] = {
	"GET",
	"HEAD",
	"POST",
	"PUT",
	"DELETE",
	"TRACE",
	"OPTIONS",
	"CONNECT",
	"PATCH"
};

const char *http_method_to_string(http_method_t method)
{
	if (method < 0 || method > HTTP_PATCH)
		return (NULL);
	return (http_method_names[method]);
}