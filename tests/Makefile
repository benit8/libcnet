##
## EPITECH PROJECT, 2018
## cnet
## File description:
## tests / Makefile
##

CFLAGS	+=	-I../include/
CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-g3

LDFLAGS	+=	-L../
LDFLAGS	+=	-lcnet

.c:
	gcc $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	find -type f -executable -delete