/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ip_address / from.c
*/

#include "ip_address.h"

ip_address_t ip_address_from_string(const char *address)
{
	struct addrinfo hints;
	struct addrinfo *result = NULL;
	uint32_t ip;

	if (strcmp(address, "255.255.255.255") == 0)
		return (INADDR_BROADCAST);
	else if (strcmp(address, "0.0.0.0") == 0)
		return (INADDR_ANY);
	if ((ip = inet_addr(address)) != INADDR_NONE)
		return (ip);
	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	if (getaddrinfo(address, NULL, &hints, &result) == 0) {
		if (!result)
			return (INADDR_NONE);
		ip = ((struct sockaddr_in *)result->ai_addr)->sin_addr.s_addr;
		freeaddrinfo(result);
		return (ip);
	}
	return (INADDR_NONE);
}

ip_address_t ip_address_from_bytes(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	return (htonl((a << 24) | (b << 16) | (c << 8) | d));
}

ip_address_t ip_address_from_integer(uint32_t address)
{
	return (htonl(address));
}