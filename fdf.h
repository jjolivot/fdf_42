/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:05:15 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/19 23:25:33 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H
#define WIN_SIZE 1000

#include "minilibx_macos/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"
#include <math.h>

typedef struct	s_id
{
	void	*win;
	void	*sess;
	void	*img;
	char	*img_str;
}				t_id;

typedef struct	s_coor
{
	t_id		*id;
	int			i_max;
	int			j_max;
	int			**tab;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	float		zoom;
	int			x_offset;
	int			y_offset;
}				t_coor;

void	ft_put_template(t_id id);
void	*ft_new_img(int size_line, int line_nbr, void *sess, char **img_string);
void	ft_draw_line(int point_1[2], int point_2[2], t_id id);
int		ft_get_coor(t_coor info, int i, int j, int (*point)[2]);
void	ft_fill_pixel(char **img_str, int x, int y, int color);
void	ft_line_from_tab(t_coor info, int i, int j, t_id id);
void	ft_draw_map(t_coor info, t_id id);
t_coor	ft_file_to_tab(char *filepath, int line_nbr);
int		ft_parsing(int argc, char **argv);

#endif
