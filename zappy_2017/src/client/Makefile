##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile zappy_ia
##

NAME    = zappy_ai

CC  = gcc
RM  = rm -f
CP  = cp

SRCS	=	./cmd.c                 \
            ./get_arg_client.c      \
            ./handle_connection.c   \
            ./handle_signal.c       \
            ./ia.c                  \
            ./main.c                \
            ./manage_socket.c       \
            ./parse_arg_client.c    \
            ./parse_cmd.c           \


OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I ../../include
CFLAGS	+=	-Wall -Wextra -std=c11 -pedantic -D_GNU_SOURCE -g
LDFLAGS =   -L../../ -lsocket -ltools

all:		$(NAME)

$(NAME):	$(OBJS)
		    $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
		    $(CP) $(NAME) ../../$(NAME)

clean:
		    $(RM) $(OBJS)

fclean:		clean
		    $(RM) $(NAME)
		    $(RM) ../../$(NAME)

re:		    fclean all

.PHONY:		all clean fclean re
