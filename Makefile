# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtemel <mtemel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 18:24:32 by mtemel            #+#    #+#              #
#    Updated: 2023/05/17 13:31:50 by mtemel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -g -std=c++98
SRCS = $(wildcard headers/*.cpp srcs/*.cpp cmds/*.cpp)
OBJS = $(SRCS:.cpp = .o)

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
		@echo "\033[1;32mCOMPILED SUCCESSFULLY\033[0m"

all: $(NAME)

clean:
		@echo "\033[1;32mCLEAN\033[0m"
		@rm -rf $(NAME)

fclean:
		@echo "\033[1;32mFCLEAN\033[0m"
		@make clean

re:
		@echo "\033[1;32mREMAKE\033[0m"
		@make fclean
		@make all

exe:
		@echo "\033[1;32mSTART EXECUTING\033[0m"
		@./$(NAME)
		@echo "\033[1;32mDONE EXECUTING\033[0m"
