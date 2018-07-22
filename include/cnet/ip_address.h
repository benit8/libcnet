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

#include "utils.h"

////////////////////////////////////////////////////////////////////////////////

#define CNET_IP_ADDRESS

////////////////////////////////////////////////////////////////////////////////

#define IP_NONE		(ip_address_from_integer(-1))
#define IP_ANY		(ip_address_from_bytes(0, 0, 0, 0))
#define IP_LOCALHOST	(ip_address_from_bytes(127, 0, 0, 1))
#define IP_BROADCAST	(ip_address_from_bytes(255, 255, 255, 255))

#define PORT_ANY	(0)
#define PORT_FTP	(21)
#define PORT_SSH	(22)
#define PORT_HTTP	(80)
#define PORT_IRC	(194)
#define PORT_HTTPS	(443)

#define STR2IP(s)	(ip_address_from_string(s))
#define INT2IP(i)	(ip_address_from_integer(i))
#define IP2STR(ip)	(ip_address_to_string(ip))
#define IP2INT(ip)	(ip_address_to_integer(ip))

////////////////////////////////////////////////////////////////////////////////

typedef uint32_t ip_address_t;

////////////////////////////////////////////////////////////////////////////////

ip_address_t ip_address_from_string(const char *string);
ip_address_t ip_address_from_bytes(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
ip_address_t ip_address_from_integer(uint32_t integer);

char *ip_address_to_string(ip_address_t ip);
uint32_t ip_address_to_integer(ip_address_t ip);

ip_address_t ip_address_get_local_address(void);
ip_address_t ip_address_get_public_address(int timeout);