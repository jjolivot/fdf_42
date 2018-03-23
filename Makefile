# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 16:16:12 by jjolivot          #+#    #+#              #
#    Updated: 2018/03/23 16:51:10 by jjolivot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -framework OpenGL -framework AppKit

LIB = -I libft/libft.a

SRC = main.c ft_draw_map.c ft_file_to_tab.c ft_img.c get_next_line.c

INC = fdf.h get_next_line.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft re
	make -C minilibx_macos re
	$(CC) $(CFLAGS) $(LIB) $(MLX_FLAGS) $(SRC) $(INC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all
