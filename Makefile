# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 16:16:12 by jjolivot          #+#    #+#              #
#    Updated: 2018/03/28 18:27:53 by jjolivot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = -L minilibx_macos -lmlx

MLX_FLAGS = -framework OpenGL -framework AppKit

LIB = -I usr/local/include libft/libft.a

SRC = main.c ft_draw_map.c ft_file_to_tab.c ft_img.c get_next_line.c \
	  ft_draw_map_suite.c ft_parsing.c

INC = fdf.h get_next_line.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft re
	make -C minilibx_macos re
	$(CC) $(CFLAGS) $(LIB) $(MLX) $(MLX_FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all
