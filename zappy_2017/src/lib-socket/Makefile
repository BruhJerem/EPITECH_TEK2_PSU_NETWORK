##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Lib poll socket Makefile
##

# Generated file name
NAME    = libsocket.a

# Shell commands
CC      = gcc
RM      = rm -f
CP      = cp

# Sources files
SRCS	= socket.c \
          socket_manipulation.c

# Object files compilation
OBJS	= $(SRCS:.c=.o)

# Compilation flags
CFLAGS  = -I../../include
CFLAGS  += -W -Wall -Wextra -pedantic -std=c11 -fPIC

all: $(NAME)

$(NAME): $(OBJS)
	 ar rc -o $@ $^
	 $(CP) $(NAME) ../../$(NAME)

clean:
	 $(RM) $(OBJS)

fclean: clean
	 $(RM) $(NAME)
	 $(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
