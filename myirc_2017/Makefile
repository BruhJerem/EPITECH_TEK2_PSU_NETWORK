##
## EPITECH PROJECT, 2018
## PSU_myirc_2017
## File description:
## MyIRC Makefile (Server && Client)
##

SERVER_NAME = server
CLIENT_NAME = client

CC	= gcc
RM	= rm -f

SERVER_SRCS = src/server/main.c \
                src/server/socket.c \
                src/server/init_server.c \
                src/server/start_process.c \
                src/server/handle_readable.c \
                src/server/check_close_connection.c \
                src/server/access_client.c \
                src/server/action_client.c \
                src/server/information_client.c \
                src/server/user_registration.c \
                src/server/access_channel.c \
                src/server/action_channel.c \
                src/server/information_channel.c \
                src/server/nick_registration.c \
                src/server/join.c \
                src/server/list.c \
                src/server/part.c \
                src/server/names.c \
                src/server/private_msg.c \
                src/server/send_client.c \
                src/server/whois.c \
                src/server/quit.c \
                src/server/propagation.c \
                src/server/parsing.c

CLIENT_SRCS = src/client/main.c \
              src/client/client.c \
              src/client/action.c \
              src/client/socket.c \
              src/client/utils.c \
              src/client/check.c \
              src/client/commands/server.c \
              src/client/commands/channel.c \
              src/client/commands/user.c \
              src/client/commands/misc.c

COMMON_SRCS = src/common/socket.c \
                src/common/str_to_wordtab.c \
                src/common/fix_buffer.c \
                src/common/rebind.c \
                src/common/nmatch.c \
                src/common/tab_len.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

CFLAGS = -Iinclude
CFLAGS += -W -Wall -Wextra -pedantic

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(COMMON_OBJS) $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) $(COMMON_OBJS) -o $(SERVER_NAME) $(LDFLAGS)

$(CLIENT_NAME): $(COMMON_OBJS) $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) $(COMMON_OBJS) -o $(CLIENT_NAME) $(LDFLAGS)

clean:
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_OBJS)
	$(RM) $(COMMON_OBJS)

fclean: clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
