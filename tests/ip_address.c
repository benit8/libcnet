/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** tests / ip_address.c
*/

#include <stdio.h>
#include "cnet/ip_address.h"

int main(void)
{
	ip_address_t pub = ip_address_get_public_address(0);

	printf("%s\n", ip_address_to_string(pub));
	return (0);
}