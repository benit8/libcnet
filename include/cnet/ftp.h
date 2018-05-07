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

#define CNET_FTP

////////////////////////////////////////////////////////////////////////////////

typedef enum ftp_transfer_mode
{
	FTP_BINARY,
	FTP_ASCII
} ftp_transfer_mode_t;

typedef enum ftp_status
{
	FTP_RESTART_MARKER_REPLY		= 110,
	FTP_SERVICE_READY_SOON			= 120,
	FTP_DATA_CONNECTION_ALREADY_OPENED	= 125,
	FTP_OPENING_DATA_CONNECTION		= 150,

	FTP_OK					= 200,
	FTP_POINTLESS_COMMAND			= 202,
	FTP_SYSTEM_STATUS			= 211,
	FTP_DIRECTORY_STATUS			= 212,
	FTP_FILE_STATUS				= 213,
	FTP_HELP_MESSAGE			= 214,
	FTP_SYSTEM_TYPE				= 215,
	FTP_SERVICE_READY			= 220,
	FTP_CLOSING_CONNECTION			= 221,
	FTP_DATA_CONNECTION_OPENED		= 225,
	FTP_CLOSING_DATA_CONNECTION		= 226,
	FTP_ENTERING_PASSIVE_MODE		= 227,
	FTP_LOGGED_IN				= 230,
	FTP_FILE_ACTION_OK			= 250,
	FTP_DIRECTORY_OK			= 257,

	FTP_NEED_PASSWORD			= 331,
	FTP_NEED_ACCOUNT_TO_LOGIN		= 332,
	FTP_NEED_INFORMATION			= 350,

	FTP_SERVICE_UNAVAILABLE			= 421,
	FTP_DATA_CONNECTION_UNAVAILABLE		= 425,
	FTP_TRANSFER_ABORTED			= 426,
	FTP_FILE_ACTION_ABORTED			= 450,
	FTP_LOCAL_ERROR				= 451,
	FTP_INSUFFICIENT_STORAGE_SPACE		= 452,

	FTP_COMMAND_UNKNOWN			= 500,
	FTP_PARAMETERS_UNKNOWN			= 501,
	FTP_COMMAND_NOT_IMPLEMENTED		= 502,
	FTP_BAD_COMMAND_SEQUENCE		= 503,
	FTP_PARAMETER_NOT_IMPLEMENTED		= 504,
	FTP_NOT_LOGGED_IN			= 530,
	FTP_NEED_ACCOUNT_TO_STORE		= 532,
	FTP_FILE_UNAVAILABLE			= 550,
	FTP_PAGE_TYPE_UNKNOWN			= 551,
	FTP_NOT_ENOUGH_MEMORY			= 552,
	FTP_FILENAME_NOT_ALLOWED		= 553,

	FTP_INVALID_RESPONSE			= 1000,
	FTP_CONNECTION_FAILED			= 1001,
	FTP_CONNECTION_CLOSED			= 1002,
	FTP_INVALID_FILE			= 1003
} ftp_status_t;

////////////////////////////////////////////////////////////////////////////////

typedef struct ftp_response
{
	ftp_status_t status;
	char *message;
} ftp_response_t;

typedef struct ftp
{
	tcp_socket_t *socket;
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