# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/23 22:16:26 by yasinsensoy       #+#    #+#              #
#    Updated: 2023/05/02 16:23:28 by ysensoy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
SRCS = $(wildcard headers/*.cpp srcs/*.cpp cmds/*.cpp)
OBJ = $(SRCS:.cpp = .o)

$(NAME): $(OBJ)
	@$(CC) $(SRCS) -o $(NAME)
	@echo "\033[1;92mCompiled succesfully..\033[0m"

all: $(NAME)

clean:
	rm -rf  $(NAME)

fclean: clean


re: fclean all

.PHONY: all clean fclean re
