/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:07:26 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/28 17:31:03 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_draw_map(t_coor info, t_id id)
{
	int		i;
	int		j;

	i = -1;
	while (++i < info.i_max)
	{
		j = -1;
		while (++j < info.j_max)
		{
			ft_line_from_tab(info, i, j, id);
		}
	}
	mlx_put_image_to_window(id.sess, id.win, id.img, 0, 0);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
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

void		ft_draw_line_norme(int (*e)[8], int point_1[2], int point_2[2])
{
	(*e)[3] = sqrt((point_1[0] - point_2[0]) * (point_1[0] - point_2[0]) -
			((point_1[1] - point_2[1]) * (point_1[1] - point_2[1])));
	(*e)[4] = ft_abs(point_2[0] - point_1[0]);
	(*e)[5] = ft_abs(point_2[1] - point_1[1]);
	(*e)[7] = point_1[0] < point_2[0] ? 1 : -1;
	(*e)[6] = point_1[1] < point_2[1] ? 1 : -1;
	(*e)[0] = ((*e)[4] > (*e)[5] ? (*e)[4] : -(*e)[5]) / 2;
}

void		ft_draw_line(int point_1[2], int point_2[2], int color[2], t_id id)
{
	int	e[8];

	e[2] = 0;
	if (point_1[0] == point_2[0])
		ft_draw_horizontal(point_1, point_2, color, id);
	else
	{
		ft_draw_line_norme(&e, point_1, point_2);
		while (!(point_1[0] == point_2[0] && point_1[1] == point_2[1]))
		{
			ft_fill_pixel(&id.img_str, point_1[0], point_1[1], color[1]);
			e[1] = 2 * e[0];
			e[2]++;
			if (e[1] >= -e[5])
			{
				e[0] -= e[5];
				point_1[0] += e[7];
			}
			else if (e[1] <= e[5])
			{
				e[0] += e[4];
				point_1[1] += e[6];
			}
		}
	}
}
