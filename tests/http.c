/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tests / http.c
*/

#include <stdio.h>
#include "cnet/http.h"

int main(void)
{
	http_t *http = http_create("127.0.0.1", 80);
	// printf("http_t:\n");
	// printf("\tConnection: %d\n", http->connection->handle);
	// printf("\tHost Name: %s\n", http->host_name);
	// printf("\tIP: %s\n", ip_address_to_string(http->host));
	// printf("\tPort: %hu\n", http->port);


	http_request_t *req = http_request_create("/", HTTP_GET, NULL);
	// printf("http_request_t:\n");
	// printf("\tURI: %s\n", req->uri);
	// printf("\tMethod: %s\n", http_method_to_string(req->method));
	// printf("\tFields: %zu\n", req->field_count);
	// for (size_t i = 0; i < req->field_count; ++i)
	// 	printf("\t\t%s: %s\n", req->field_table[i].name, req->field_table[i].value);
	// printf("\tBody: [%s]\n", req->body);
	// printf("\tVersion: %u.%u\n", req->major_version, req->minor_version);


	http_response_t *res = http_send_request(http, req, 10);
	printf("%d\n", res->status);
	if (res->status < 400)
		printf("[%s]\n", res->body);


	http_response_destroy(res);
	http_request_destroy(req);
	http_destroy(http);
	return (0);
}