/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:07:26 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/23 17:24:44 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_map(t_coor info, t_id id)
{
	int		i;
	int		j;

	i = -1;
	while(++i < info.i_max)
		{
			j = -1;
			while (++j < info.j_max)
			{
				ft_line_from_tab(info, i, j, id);
			}
		}
	mlx_put_image_to_window(id.sess, id.win, id.img, 0, 0);
}

void		ft_line_from_tab(t_coor info, int i, int j, t_id id)
{
	int		point_1[2];
	int		point_2[2];
	int		ij[2];
	int		colors[2];

	ij[0] = i;
	ij[1] = j;
	ft_get_coor(info, i, j, &point_1);
	if (i < info.i_max - 1)
	{
		ft_get_coor(info, (i + 1), j, &point_2);
		ft_colors(info, ij, &colors, 0);
		ft_draw_line(point_1, point_2, colors, id);
	}
	ft_get_coor(info, i, j, &point_1);
	if (j < info.j_max - 1)
	{
		ft_get_coor(info, i, (j + 1), &point_2);
		ft_colors(info, ij, &colors, 1);
		ft_draw_line(point_1, point_2, colors, id);
	}
}

static	void	ft_swap(int (*colors)[2])
{
	int a;

	a = (*colors)[0];
	(*colors)[0] = (*colors)[1];
	(*colors)[1] = a;

}

int		ft_colors(t_coor info, int ij[2], int (*colors)[2], int mode)
{
	if (info.z_max == info.z_min)
	{
		(*colors)[0] = 0xFFFFFF;
		(*colors)[1] = 0xFFFFFF;
		return (1);
	}
	(*colors)[0] = 0xFFFFFF - info.tab[ij[0]][ij[1]] * (0x00FFFF /
			(info.z_max - info.z_min));
	if (!mode)
	{
		(*colors)[1] = 0xFFFFFF - info.tab[ij[0] + 1][ij[1]] * (0x00FFFF /
				(info.z_max - info.z_min));
		if (info.tab[ij[0] + 1][ij[1]] < info.tab[ij[0]][ij[1]])
			ft_swap(colors);
	}
	else
	{
		(*colors)[1] = 0xFFFFFF - info.tab[ij[0]][ij[1] + 1] * (0x00FFFF /
				(info.z_max - info.z_min));
		if (info.tab[ij[0]][ij[1] + 1] < info.tab[ij[0]][ij[1]])
			ft_swap(colors);
	}
	return (1);
}
//stocke les coordonne a l'adresse pointe par *point
// i = y, j = x
int	ft_get_coor(t_coor info, int i, int j, int (*point)[2])
{
	int		y0;
	int		z0;
	int		x1;
	int		z1;

	info.y_angle = (M_PI / 180) * info.y_angle;
	info.x_angle = (M_PI / 180) * info.x_angle;
	info.z_angle = (M_PI / 180) * info.z_angle;
	y0 = cos(info.x_angle) * i * 20 + sin(info.x_angle) * info.height *
		info.tab[i][j];
	z0 = -sin(info.x_angle) * i * 20 + cos(info.x_angle) * info.height
		* info.tab[i][j];
	x1 = cos(info.y_angle) * j * 20 - sin(info.y_angle) * z0;
	z1 = sin(info.y_angle) * j * 20 + cos(info.y_angle) * z0;
	(*point)[0] = (cos(info.z_angle) * x1 + sin(info.z_angle)
		* y0) * info.zoom + WIN_SIZE / 4 + info.x_offset;
	(*point)[1] = (-sin(info.z_angle) * x1 + cos(info.z_angle)
		* y0) * info.zoom + WIN_SIZE / 4 + info.y_offset;
	return (1);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return(-nbr);
	return(nbr);
}

static void	ft_draw_horizontal(int point_1[2], int point_2[2],
		int color[2], t_id id)
{
	int	tot_d;
	int	cov_d;

	tot_d = ft_abs(point_1[1] - point_2[1]);
	cov_d = 0;
	if (point_1[1] > point_2[1])
		while (point_1[1]-- > point_2[1])
		{
			cov_d++;
			ft_fill_pixel(&id.img_str, point_1[0], point_1[1], color[1]);
		}
	else
		while (point_1[1]++ <= point_2[1] && point_1[0] < WIN_SIZE &&
				point_1[0] > 0 && point_1[1] > 0 && point_1[1] < WIN_SIZE)
		{
			cov_d++;
			ft_fill_pixel(&id.img_str, point_1[0], point_1[1], color[1]);
		}
}



void ft_draw_line(int point_1[2], int point_2[2], int color[2], t_id id)
{
	int	e[4];
	int	dx;
	int	dy;
	int	sy;
	int	sx;

	e[2] = 0;
	if (point_1[0] == point_2[0])
		ft_draw_horizontal(point_1, point_2, color, id);
	else
	{
		e[3] = sqrt((point_1[0] - point_2[0]) * (point_1[0] - point_2[0]) -
				((point_1[1] - point_2[1]) * (point_1[1] - point_2[1])));
		dx = ft_abs(point_2[0] - point_1[0]);
		dy = ft_abs(point_2[1] - point_1[1]);
		sx = point_1[0] < point_2[0] ? 1 : -1;
		sy = point_1[1] < point_2[1] ? 1 : -1;
		e[0] = (dx > dy ? dx : -dy) / 2;
		while (!(point_1[0] == point_2[0] && point_1[1] == point_2[1]))
		{
			ft_fill_pixel(&id.img_str, point_1[0], point_1[1], color[1]);
			e[1] = 2 * e[0];
			e[2]++;
			if (e[1] >= -dy)
			{
				e[0] -= dy;
				point_1[0] += sx;
			}
			else if (e[1] <= dy)
			{
				e[0] += dx;
				point_1[1] += sy;
			}
		}
	}
}
