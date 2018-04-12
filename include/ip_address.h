/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ip_address.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////

// Arbitrary invalid ip address
#define IP_NONE		(ip_address_from_bytes(0, 42, 42, 42))
#define IP_ANY		(ip_address_from_bytes(0, 0, 0, 0))
#define IP_LOCALHOST	(ip_address_from_bytes(127, 0, 0, 1))
#define IP_BROADCAST	(ip_address_from_bytes(255, 255, 255, 255))

////////////////////////////////////////////////////////////////////////////////

typedef uint32_t ip_address_t;

////////////////////////////////////////////////////////////////////////////////

ip_address_t ip_address_from_string(const char *);
ip_address_t ip_address_from_bytes(uint8_t, uint8_t, uint8_t, uint8_t);
ip_address_t ip_address_from_integer(uint32_t);

char *ip_address_to_string(ip_address_t);
uint32_t ip_address_to_integer(ip_address_t);

ip_address_t ip_address_get_local_address(void);
ip_address_t ip_address_get_public_address(int timeout);