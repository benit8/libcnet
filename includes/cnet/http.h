/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** http.h
*/

#pragma once
#define _GNU_SOURCE

////////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <stdio.h>

#include "tcp_socket.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_HTTP

////////////////////////////////////////////////////////////////////////////////

typedef enum http_method
{
	HTTP_GET,
	HTTP_HEAD,
	HTTP_POST,
	HTTP_PUT,
	HTTP_DELETE,
	HTTP_TRACE,
	HTTP_OPTIONS,
	HTTP_CONNECT,
	HTTP_PATCH
} http_method_t;

typedef enum http_status
{
	// 1xx: informational responses
	HTTP_CONTINUE				= 100,
	HTTP_SWITCHING_PROTOCOLS		= 101,
	HTTP_PROCESSING				= 102,
	HTTP_EARLY_HINTS			= 103,

	// 2xx: success
	HTTP_OK					= 200,
	HTTP_CREATED				= 201,
	HTTP_ACCEPTED				= 202,
	HTTP_NON_AUTHORITATIVE_INFORMATION	= 203,
	HTTP_NO_CONTENT				= 204,
	HTTP_RESET_CONTENT			= 205,
	HTTP_PARTIAL_CONTENT			= 206,
	HTTP_MULTI_STATUS			= 207,
	HTTP_ALREADY_REPORTED			= 208,
	HTTP_IM_USED				= 226,

	// 3xx: redirection
	HTTP_MULTIPLE_CHOICES			= 300,
	HTTP_MOVED_PERMANENTLY			= 301,
	HTTP_FOUND				= 302,
	HTTP_SEE_OTHER				= 303,
	HTTP_NOT_MODIFIED			= 304,
	HTTP_USE_PROXY				= 305,
	HTTP_SWITCH_PROXY			= 306,
	HTTP_TEMPORARY_REDIRECT			= 307,
	HTTP_PERMANENT_REDIRECT			= 308,

	// 4xx: client error
	HTTP_BAD_REQUEST			= 400,
	HTTP_UNAUTHORIZED			= 401,
	HTTP_PAYMENT_REQUIRED			= 402,
	HTTP_FORBIDDEN				= 403,
	HTTP_NOT_FOUND				= 404,
	HTTP_METHOD_NOT_ALLOWED			= 405,
	HTTP_NOT_ACCEPTABLE			= 406,
	HTTP_PROXY_AUTHENTICATION_REQUIRED	= 407,
	HTTP_REQUEST_TIMEOUT			= 408,
	HTTP_CONFLICT				= 409,
	HTTP_GONE				= 410,
	HTTP_LENGTH_REQUIRED			= 411,
	HTTP_PRECONDITION_FAILED		= 412,
	HTTP_PAYLOAD_TOO_LARGE			= 413,
	HTTP_URI_TOO_LONG			= 414,
	HTTP_UNSUPPORTED_MEDIA_TYPE		= 415,
	HTTP_RANGE_NOT_SATISFIABLE		= 416,
	HTTP_EXPECTATION_FAILED			= 417,
	HTTP_IM_A_TEAPOT			= 418,
	HTTP_MISREDIRECTED_REQUEST		= 421,
	HTTP_UNPROCESSABLE_ENTITY		= 422,
	HTTP_LOCKED				= 423,
	HTTP_FAILED_DEPENDENCY			= 424,
	HTTP_UPGRADE_REQUIRED			= 426,
	HTTP_PRECONDITION_REQUIRED		= 428,
	HTTP_TOO_MANY_REQUESTS			= 429,
	HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE	= 431,
	HTTP_UNAVAILABLE_FOR_LEGAL_REASONS	= 451,

	// 5xx: server error
	HTTP_INTERNAL_SERVER_ERROR		= 500,
	HTTP_NOT_IMPLEMENTED			= 501,
	HTTP_BAD_GATEWAY			= 502,
	HTTP_SERVICE_UNAVAILABLE		= 503,
	HTTP_GATEWAY_TIMEOUT			= 504,
	HTTP_VERSION_NOT_SUPPORTED		= 505,
	HTTP_VARIANT_ALSO_NEGOTIATES		= 506,
	HTTP_INSUFFICIENT_STORAGE		= 507,
	HTTP_LOOP_DETECTED			= 508,
	HTTP_NOT_EXTENDED			= 510,
	HTTP_NETWORK_AUTHENTICATION_REQUIRED	= 511,

	// 10xx: CNET custom codes
	HTTP_INVALID_RESPONSE			= 1000,
	HTTP_CONNECTION_FAILED			= 1001
} http_status_t;

////////////////////////////////////////////////////////////////////////////////

typedef struct http_field
{
	char *name;
	char *value;
} http_field_t;

typedef struct http_request
{
	char *uri;
	http_method_t method;
	http_field_t *field_table;
	size_t field_count;
	char *body;
	unsigned int major_version;
	unsigned int minor_version;
} http_request_t;

typedef struct http_response
{
	http_status_t status;
	http_field_t *field_table;
	size_t field_count;
	char *body;
	unsigned int major_version;
	unsigned int minor_version;
} http_response_t;

typedef struct http
{
	tcp_socket_t *connection;
	ip_address_t host;
	char *host_name;
	unsigned short port;
} http_t;

////////////////////////////////////////////////////////////////////////////////

const char *http_method_to_string(http_method_t method);

http_request_t *http_request_create(const char *uri, http_method_t method,
	const char *body);
void http_request_destroy(http_request_t *request);
http_request_t *http_request_copy(http_request_t *request);
void http_request_set_field(http_request_t *request, const char *field,
	const char *value);
bool http_request_has_field(http_request_t *request, const char *field);
void http_request_set_method(http_request_t *request, http_method_t method);
void http_request_set_uri(http_request_t *request, const char *uri);
void http_request_set_http_version(http_request_t *request, unsigned int major,
	unsigned int minor);
void http_request_set_body(http_request_t *request, const char *body);
char *http_request_prepare(const http_request_t *request);

http_response_t *http_response_create(void);
void http_response_destroy(http_response_t *response);
char *http_response_get_field(http_response_t *response,
	const char *field);
void http_response_set_field(http_response_t *response, const char *field,
	const char *value);
bool http_response_has_field(http_response_t *request, const char *field);
void http_response_parse(http_response_t *response, char *data, size_t len);

http_t *http_create(const char *host, unsigned short port);
void http_destroy(http_t *http);
void http_set_host(http_t *http, const char *host, unsigned short port);
http_response_t *http_send_request(http_t *http, http_request_t *request,
	int timeout);