NAME	= zappy_ui

CC	= g++
RM	= rm -f
CP  = cp

SRCS	= ConnectionHandler.cpp \
          Map.cpp \
          Sprite.cpp \
          Window.cpp \
          Parsing.cpp \
          main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I../../include
CPPFLAGS += -W -Wall -Wextra -std=c++14
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L../../ -lsocket -lpthread

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
