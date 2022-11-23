NAME = 	webserv
CFLAGS = -Wall -Wextra -Werror
CC = c++

SRCS = main.cpp Parser.cpp server.cpp ServerData.cpp socket.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

%.o:%.cpp general_info.hpp Parser.hpp server.hpp ServerData.hpp socket.hpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all