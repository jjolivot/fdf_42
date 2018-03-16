/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 23:45:44 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/12 17:55:03 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "fdf.h"
	static	void	*sess_id;
	static	void	*win_id;
	static	void	*img_id;
	static	char	*img_str;

int key_hook(int kc, int *param)
{
	int i = (int)param[0];
	int j = param[1];

	if (kc == 126 && j > 0)
		j--;
	if (kc == 125 && j < 500)
		j++;
	if (kc == 123 && i > 0)
		i--;
	if (kc == 124 && i < 500)
		i++;
	param[0] = i;
	param[1] = j;
	mlx_pixel_put(sess_id, win_id, param[0], param[1], 0xFFFFFF);
//	printf("tg %d\n", kc);
	return (1);
}

static void	ft_draw_horizontal(int point_1[2], int point_2[2])
{
	if (point_1[1] > point_2[1])
		while (point_1[1]-- > point_2[1])
			mlx_pixel_put(sess_id, win_id, point_1[0], point_1[1], 0xFFFFFF);
	else
		while (point_1[1]++ <= point_2[1])
			mlx_pixel_put(sess_id, win_id, point_1[0], point_1[1], 0xFFFFFF);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return(-nbr);
	return(nbr);
}

void ft_draw_line(int point_1[2], int point_2[2])
{
	int	e[2];
	int	dx;
	int	dy;
	int	sy;
	int	sx;

	if (point_1[0] == point_2[0])
		ft_draw_horizontal(point_1, point_2);
	else
	{
		dx = ft_abs(point_2[0] - point_1[0]);
		dy = ft_abs(point_2[1] - point_1[1]);
		sx = point_1[0] < point_2[0] ? 1 : -1;
		sy = point_1[1] < point_2[1] ? 1 : -1;
		e[0] = (dx > dy ? dx : -dy) / 2;
		while (!(point_1[0] == point_2[0] && point_1[1] == point_2[1]))
		{
			mlx_pixel_put(sess_id, win_id, point_1[0], point_1[1], 0xFFFFFF);
			e[1] = 2 * e[0];
			if (e[1] > -dy && (e[0] -= dy) > -999999)
				point_1[0] += sx;
			if (e[1] < dy && (e[0] += dx) > -9999999)
				point_1[1] += sy;
		}
			mlx_pixel_put(sess_id, win_id, point_1[0], point_1[1], 0xFFFFFF);
	}
}

int	mouse_hook(int button, int x, int y, void *param)
{
	static int point_1[2];
	static int point_2[2];
	
	point_1[0] = 250; point_1[1] = 250;
		point_2[0] = x; point_2[1] = y;
		printf("x : %d, y : %d\n", x, y);

	ft_draw_line(point_1, point_2);
	return (1);
}
/*
int main()
{

	int *coor;
	coor = (int *)malloc(sizeof(int) * 4);
	coor[0] = 250;
	coor[1] = 250;
	int coor2[2] = {300, 356};
	sess_id = mlx_init();
	win_id = mlx_new_window(sess_id, WIN_SIZE, WIN_SIZE, "mlx 42");
	//ft_draw_line(coor, coor2);
//	mlx_pixel_put(sess_id, win_id, coor[0], coor[1], 0xFFFFFF);
//	mlx_mouse_hook(win_id, mouse_hook, coor);
	img_id = ft_new_img(WIN_SIZE, WIN_SIZE, sess_id, &img_str);
	ft_fill_pixel(&img_str, 500, 500, 0xFFFFFF);
	mlx_put_image_to_window(sess_id, win_id, img_id, 0, 0);
	printf("test\n");
	mlx_loop(sess_id);

	return (1);
}

int	main()
{
	void	*sess_id;
	void	*win_id;
	int i;
	int j;

	sess_id = mlx_init();
	win_id = mlx_new_window(sess_id, 1000, 1000, "prout");
	mlx_pixel_put(sess_id, win_id, 250, 250, 0xFFFFFF);

	i = -1;
	j = -1;
	while (++i < 100)
	{
		while (++j < 100)
			mlx_pixel_put(sess_id, win_id, 250 + i, 250 + j, 0xFFFFFF);
		j = -1;
	}
//	mlx_key_hook(win_id, ft_putchar,(void *)0);
	mlx_loop(win_id);
	return (0);
}*/
