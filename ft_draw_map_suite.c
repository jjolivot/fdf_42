/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 19:25:08 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/27 19:34:21 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_line_from_tab(t_coor info, int i, int j, t_id id)
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

int				ft_colors(t_coor info, int ij[2], int (*colors)[2], int mode)
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

int				ft_get_coor(t_coor info, int i, int j, int (*point)[2])
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
