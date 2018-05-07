##
## EPITECH PROJECT, 2018
## cnet
## File description:
## Makefile
##

PROJECT	=	cnet
NAME	=	libcnet.a

SRC_DIR	=	sources/

SOURCES	=	http/http.c				\
		http/http_request.c			\
		http/method.c				\
		http/request.c				\
		http/request_fields.c			\
		http/request_prepare.c			\
		http/request_setters.c			\
		http/response.c				\
		http/response_fields.c			\
		http/response_parse.c			\
		ip_address/from.c			\
		ip_address/to.c				\
		ip_address/getters.c			\
		sockets/impl/blocking.c			\
		sockets/impl/error.c			\
		sockets/impl/socket.c			\
		sockets/tcp/blocking.c			\
		sockets/tcp/connection.c		\
		sockets/tcp/local.c			\
		sockets/tcp/remote.c			\
		sockets/tcp/socket.c			\
		sockets/tcp/transmission.c		\
		socket_selector/add.c			\
		socket_selector/clear.c			\
		socket_selector/is_ready.c		\
		socket_selector/remove.c		\
		socket_selector/socket_selector.c	\
		socket_selector/wait.c			\
		tcp_listener/blocking.c			\
		tcp_listener/connection.c		\
		tcp_listener/listener.c			\
		tcp_listener/local.c

################################################################################

include ./utils.make