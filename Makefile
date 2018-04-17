##
## EPITECH PROJECT, 2018
## cnet
## File description:
## Makefile
##

PROJECT	=	cnet
NAME	=	libcnet.a

SRC_DIR	=	src/

SOURCES	=	ip_address/from.c			\
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
		tcp_listener/blocking.c			\
		tcp_listener/connection.c		\
		tcp_listener/listener.c			\
		tcp_listener/local.c

SRCS	=	$(addprefix $(SRC_DIR),$(SOURCES))
OBJS	=	$(SRCS:.c=.o)

################################################################################

CFLAGS	+=	-Iinclude/
CFLAGS	+=	-W -Wall -Wextra

LDFLAGS	+=

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	gcc

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug: CFLAGS += -g3
debug: $(NAME)

$(NAME): prebuild $(OBJS)
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Building $(NAME)"
	@ (ar rc $(NAME) $(OBJS) $(LDFLAGS) && ranlib $(NAME)) && \
	  ($(PRINT) " => $(GREEN)Done$(RESET)\n" ; exit 0) || \
	  ($(PRINT) " => $(RED)Fail$(RESET)\n" ; exit 1)

prebuild:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug

.c.o:
	@ $(CC) -c $< -o $@ $(CFLAGS) && \
	  ($(PRINT) "  $(GREEN)[OK]$(CYAN)  %b$(RESET)\n" $<) || \
	  ($(PRINT) "  $(RED)[XX]$(CYAN)  %b$(RESET)\n" $< ; exit 1)

.PHONY: all $(NAME) prebuild clean fclean re .c.o