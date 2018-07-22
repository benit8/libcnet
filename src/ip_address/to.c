/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ip_address / to.c
*/

#include "cnet/ip_address.h"

char *ip_address_to_string(ip_address_t address)
{
	struct in_addr addr;

	addr.s_addr = address;
	return inet_ntoa(addr);
}

uint32_t ip_address_to_integer(ip_address_t address)
{
	return ntohl(address);
}