# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 19:12:25 by ntanjaou          #+#    #+#              #
#    Updated: 2022/12/23 19:12:26 by ntanjaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	webserv
CFLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++

SRCS = main.cpp Parser.cpp ServerData.cpp server.cpp  socket.cpp request.cpp response.cpp split.cpp requestData.cpp cgi.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

%.o:%.cpp general_info.hpp Parser.hpp server.hpp ServerData.hpp socket.hpp request.hpp response.hpp requestData.hpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all