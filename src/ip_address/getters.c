/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ip_address / getters.c
*/

#include "ip_address.h"

ip_address_t ip_address_get_local_address(void)
{
	struct sockaddr_in address;
	socklen_t size = sizeof(address);
	int sock = socket(PF_INET, SOCK_DGRAM, 0);

	if (sock == -1)
		return (IP_NONE);
	bzero(&address, sizeof(struct sockaddr_in));
	address.sin_addr.s_addr = INADDR_LOOPBACK;
	address.sin_family = AF_INET;
	address.sin_port = htons(9);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)) == -1) {
		close(sock);
		return (IP_NONE);
	}
	if (getsockname(sock, (struct sockaddr *)&address, &size) == -1) {
		close(sock);
		return (IP_NONE);
	}
	close(sock);
	return (ntohl(address.sin_addr.s_addr));
}

ip_address_t ip_address_get_public_address(int timeout)
{ (void)timeout;
	// http_t *server = http_create("www.sfml-dev.org");
	// http_request_t *request = http_request_create("/ip-provider.php", HTTP_REQUEST_GET);
	// http_response_t *page = server_send_request(server, request, timeout);

	// if (http_response_get_status(page) == HTTP_RESPONSE_OK)
	// 	return (ip_address_from_string(http_response_get_body(page)));
	return (IP_NONE);
}