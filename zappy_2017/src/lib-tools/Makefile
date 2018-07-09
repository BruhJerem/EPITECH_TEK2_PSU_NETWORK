##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Lib tools Makefile
##

# Generated file name
NAME    = libtools.a

# Shell commands
CC      = gcc
RM      = rm -f
CP      = cp

# Sources files
SRCS	= tab.c \
          str_to_wordtab.c \
          string_nbr.c \
          string.c \
          circular_buffer.c

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
