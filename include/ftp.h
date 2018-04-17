/*
** EPITECH PROJECT, 2018
** cnet
** File description:
** ftp.h
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "tcp_socket.h"

////////////////////////////////////////////////////////////////////////////////

typedef enum ftp_transfer_mode
{
	BINARY,
	ASCII
} ftp_transfer_mode_t;

typedef enum ftp_status
{
	RESTART_MARKER_REPLY		= 110,
	SERVICE_READY_SOON		= 120,
	DATA_CONNECTION_ALREADY_OPENED	= 125,
	OPENING_DATA_CONNECTION		= 150,

	OK				= 200,
	POINTLESS_COMMAND		= 202,
	SYSTEM_STATUS			= 211,
	DIRECTORY_STATUS		= 212,
	FILE_STATUS			= 213,
	HELP_MESSAGE			= 214,
	SYSTEM_TYPE			= 215,
	SERVICE_READY			= 220,
	CLOSING_CONNECTION		= 221,
	DATA_CONNECTION_OPENED		= 225,
	CLOSING_DATA_CONNECTION		= 226,
	ENTERING_PASSIVE_MODE		= 227,
	LOGGED_IN			= 230,
	FILE_ACTION_OK			= 250,
	DIRECTORY_OK			= 257,

	NEED_PASSWORD			= 331,
	NEED_ACCOUNT_TO_LOGIN		= 332,
	NEED_INFORMATION		= 350,

	SERVICE_UNAVAILABLE		= 421,
	DATA_CONNECTION_UNAVAILABLE	= 425,
	TRANSFER_ABORTED		= 426,
	FILE_ACTION_ABORTED		= 450,
	LOCAL_ERROR			= 451,
	INSUFFICIENT_STORAGE_SPACE	= 452,

	COMMAND_UNKNOWN			= 500,
	PARAMETERS_UNKNOWN		= 501,
	COMMAND_NOT_IMPLEMENTED		= 502,
	BAD_COMMAND_SEQUENCE		= 503,
	PARAMETER_NOT_IMPLEMENTED	= 504,
	NOT_LOGGED_IN			= 530,
	NEED_ACCOUNT_TO_STORE		= 532,
	FILE_UNAVAILABLE		= 550,
	PAGE_TYPE_UNKNOWN		= 551,
	NOT_ENOUGH_MEMORY		= 552,
	FILENAME_NOT_ALLOWED		= 553,

	INVALID_RESPONSE		= 1000,
	CONNECTION_FAILED		= 1001,
	CONNECTION_CLOSED		= 1002,
	INVALID_FILE			= 1003
} ftp_status_t;

////////////////////////////////////////////////////////////////////////////////

typedef struct ftp_response
{
	ftp_status_t status;
	char *message;
} ftp_response_t;

typedef struct ftp
{
	tcp_socket *socket;
	char *buffer;
} ftp_t;

////////////////////////////////////////////////////////////////////////////////

void ftp_response_destroy(ftp_response_t *res);
bool ftp_response_is_ok(const ftp_response_t *res);


ftp_t *ftp_create(void);
void ftp_destroy(ftp_t *ftp);

ftp_response_t *ftp_connect(ftp_t *ftp, ip_address_t server,
	unsigned short port, int timeout);
ftp_response_t *ftp_login(ftp_t *ftp, const char *name, const char *password);
ftp_response_t *ftp_login_anonymous(ftp_t *ftp);
ftp_response_t *ftp_disconnect(ftp_t *ftp);
ftp_response_t *ftp_keep_alive(ftp_t *ftp);

ftp_response_t *ftp_download(ftp_t *ftp, const char *remote_file,
	const char *local_path, ftp_transfer_mode_t mode);
ftp_response_t *ftp_upload(ftp_t *ftp, const char *local_file,
	const char *remote_path, ftp_transfer_mode_t mode);

ftp_response_t *ftp_send_command(ftp_t *ftp, const char *command,
	const char *parameter);