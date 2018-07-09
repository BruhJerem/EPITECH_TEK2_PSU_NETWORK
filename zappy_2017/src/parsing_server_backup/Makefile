##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile zappy_ia
##

NAME	=	 zappy_ia

CC	    =	 gcc

RM	    =	 rm -f

SRCS	=	./get_arg_client.c		\
		    ./main.c		        \
		    ./parse_arg_client.c	\


OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I
CFLAGS	+=	-Wall -Wextra -std=c11 -pedantic -D_GNU_SOURCE

all:		$(NAME)

$(NAME):	$(OBJS)
		    $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		    $(RM) $(OBJS)

fclean:		clean
		    $(RM) $(NAME)

re:		    fclean all

.PHONY:		all clean fclean re
