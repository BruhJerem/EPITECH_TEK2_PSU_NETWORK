NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= ./src_server/communicate_client.c \
	  ./src_server/delete_file.c \
	  ./src_server/directory.c \
	  ./src_server/help_noop_quit.c \
	  ./src_server/lib/epur_str.c \
	  ./src_server/lib/get_next_line.c \
	  ./src_server/lib/rebind.c \
	  ./src_server/lib/str_to_wordtab.c \
	  ./src_server/list_function.c \
	  ./src_server/main.c \
	  ./src_server/protocol.c \
	  ./src_server/retr_function.c \
	  ./src_server/server.c \
	  ./src_server/start_server.c \
	  ./src_server/stor_function.c \
	  ./src_server/check_user.c \
	  ./src_server/init_protocol.c \
	  ./src_server/utils.c \
	  ./src_server/user_handling.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./src_server/lib/
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
