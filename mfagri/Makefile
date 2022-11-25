# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 17:48:48 by mfagri            #+#    #+#              #
#    Updated: 2022/11/25 22:24:33 by mfagri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = request

SRC	= server.cpp request.cpp split.cpp response.cpp

CXX = c++

CFLAGS = -Wall -Wextra -Werror
DFLAGS = -std=c++98
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp request.hpp response.hpp
	$(CXX) -c -o $@ -c $<

$(NAME): $(OBJ)
	$(CXX) $(SRC) -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	
re: fclean all