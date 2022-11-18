# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 15:24:55 by mmardi            #+#    #+#              #
#    Updated: 2022/11/18 15:36:50 by mmardi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Parser.cpp

HEADERS = Parser.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(HEADERS)
	c++ $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	c++ $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ);

fclean: clean
	@rm -rf $(NAME)

re: fclean all
