##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Server Makefile
##

NAME	= zappy_server

CC      = gcc
RM      = rm -f
CP      = cp

SRCS	= 	main.c \
		    server.c \
		    debug.c \
		    gui_client.c \
		    arg_parser/error_display.c \
            arg_parser/flags_values_fetcher.c \
            arg_parser/get_team_name.c \
            arg_parser/server_arg_parsing.c \
            arg_parser/init_struct.c \
		    cmd/cmd_router.c \
            cmd/cmd_router_gui.c \
            cmd/cmd_router_player.c \
            cmd/gui/map.c \
            cmd/gui/player.c \
            cmd/gui/team.c \
            cmd/gui/time_unit.c \
            cmd/player/broadcast_text.c \
            cmd/player/move.c \
            cmd/player/object.c \
            cmd/player/player.c \
            cmd/player/team.c \
            events/player.c \
		    game/inventory.c \
            game/player.c \
            game/team.c \
		    list/player_list.c \
            list/team_list.c \
		    map/map.c \
            map/map_generation.c \
            map/map_player.c \
            map/map_player_generation.c \
            map/map_player_orientation.c \
            map/map_player_vision.c \
		    network/incoming_connection.c \
		    network/handle_readable.c \
		    network/handle_disconnection.c

LDFLAGS = -L../../ -lsocket -ltools

OBJS	= $(SRCS:.c=.o)

CFLAGS  = -I../../include
CFLAGS += -W -Wall -Wextra -pedantic -std=c11 -D_GNU_SOURCE -g


all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	 $(CP) $(NAME) ../../$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
