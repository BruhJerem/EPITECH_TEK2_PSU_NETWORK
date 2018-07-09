##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Main Makefile
##

# Make directory
MAKE        = @make --no-print-directory -C
MAKE_CLEAN  = @make clean --no-print-directory -C
MAKE_FCLEAN = @make fclean --no-print-directory -C
MAKE_RE     = @make re --no-print-directory -C

all: compile

compile:
	 $(MAKE) ./src/lib-tools
	 $(MAKE) ./src/lib-socket
	 $(MAKE) ./src/server
	 $(MAKE) ./src/ui
	 $(MAKE) ./src/client

clean:
	 $(MAKE_CLEAN) ./src/lib-tools
	 $(MAKE_CLEAN) ./src/lib-socket
	 $(MAKE_CLEAN) ./src/server
	 $(MAKE_CLEAN) ./src/ui
	 $(MAKE_CLEAN) ./src/client

fclean:
	 $(MAKE_FCLEAN) ./src/lib-tools
	 $(MAKE_FCLEAN) ./src/lib-socket
	 $(MAKE_FCLEAN) ./src/server
	 $(MAKE_FCLEAN) ./src/ui
	 $(MAKE_FCLEAN) ./src/client

re:
	 $(MAKE_RE) ./src/lib-tools
	 $(MAKE_RE) ./src/lib-socket
	 $(MAKE_RE) ./src/server
	 $(MAKE_RE) ./src/ui
	 $(MAKE_RE) ./src/client

ui:
	 $(MAKE_RE) ./src/ui

libs:
	 $(MAKE_RE) ./src/lib-tools
	 $(MAKE_RE) ./src/lib-socket

server:
	 $(MAKE_RE) ./src/server

client:
	 $(MAKE_RE) ./src/client

.PHONY: all compile clean fclean re libs server client
