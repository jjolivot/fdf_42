# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 16:16:12 by jjolivot          #+#    #+#              #
#    Updated: 2018/02/07 16:17:18 by jjolivot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(NAME) $(SRC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
