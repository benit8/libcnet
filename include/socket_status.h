/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** socket_status.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

typedef enum socket_status
{
	SOCKET_DONE,
	SOCKET_NOT_READY,
	SOCKET_PARTIAL,
	SOCKET_DISCONNECTED,
	SOCKET_ERROR
} socket_status_t;