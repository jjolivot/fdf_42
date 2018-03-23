/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:04:31 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/23 17:19:21 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_template(t_id id, t_coor *info)
{
	mlx_string_put(id.sess, id.win, 20, 20, 0xFFFFFF, "Exit: ESC");
	mlx_string_put(id.sess, id.win, 20, 40, 0xFFFFFF,
			"Move: Num pad (2, 4, 6, 8)");
	mlx_string_put(id.sess, id.win, 20, 60, 0xFFFFFF,
			"Rotate: Arrows & Num pad (0, '.')");
	mlx_string_put(id.sess, id.win, 20, 80, 0xFFFFFF, "Zoom: +, -");
	mlx_string_put(id.sess, id.win, 20, 100, 0xFFFFFF,
			"Change Height Factor: =, /");
	mlx_string_put(id.sess, id.win, 800, 20, 0xFFFFFF, "Highest point:");
	mlx_string_put(id.sess, id.win, 800, 40, 0xFFFFFF, ft_itoa(info->z_max));
	mlx_string_put(id.sess, id.win, 800, 60, 0xFFFFFF, "Lowest point:");
	mlx_string_put(id.sess, id.win, 800, 80, 0xFFFFFF, ft_itoa(info->z_min));
}

int	ft_loop_hook(t_coor *info)
{
	ft_draw_map(*info, *(*info).id);
	mlx_put_image_to_window(info->id->sess, info->id->win, info->id->img, 0, 0);
	ft_bzero(info->id->img_str, (WIN_SIZE * WIN_SIZE * 4));
	ft_put_template(*info->id, info);

	return (0);
}

void	ft_key_hook_suite(int kc, t_coor *info)
{
	if (kc == 65)
		info->z_angle = info->z_angle - 3;
	if (kc == 82)
		info->z_angle = info->z_angle + 3;
	if (kc == 91)
		info->y_offset = info->y_offset - 10;
	if (kc == 84)
		info->y_offset = info->y_offset + 10;
	if (kc == 86)
		info->x_offset = info->x_offset - 10;
	if (kc == 88)
		info->x_offset = info->x_offset + 10;
	if (kc == 78 && info->zoom > 0.1)
		info->zoom = info->zoom - 0.2;
	if (kc == 69)
		info->zoom = info->zoom + 0.2;
	if (kc == 81 && info->height > 2)
		info->height = info->height - 1;
	if (kc == 75)
		info->height = info->height + 1;
}

int		ft_key_hook(int kc, t_coor *info)
{
	if (kc == 126)
		info->x_angle = info->x_angle + 3;
	if (kc == 125)
		info->x_angle = info->x_angle - 3;
	if (kc == 123)
		info->y_angle = info->y_angle + 3;
	if (kc == 124)
		info->y_angle = info->y_angle - 3;
	ft_key_hook_suite(kc, info);
	if (kc == 53)
		exit(1);
	return (0);
}



int	main(int argc, char **argv)
{
	t_id	id;
	t_coor	info;
	int		ret;
	int		*param[2];

	if ((ret = ft_parsing(argc, argv)) == -1)
		return (-1);
	info = ft_file_to_tab(argv[1], ret);
	if (info.tab[0][0] == -1)
		return (-1);
	id.sess = mlx_init();
	id.win = mlx_new_window(id.sess, WIN_SIZE, WIN_SIZE, "fdf");
	id.img = ft_new_img(WIN_SIZE, WIN_SIZE, id.sess, &id.img_str);
	ft_draw_map(info, id);
	info.id = &id;
	mlx_hook(id.win, 2, (1l << 8), &ft_key_hook, &info);
	mlx_loop_hook(id.sess, &ft_loop_hook, &info);
	mlx_loop(id.sess);
	return (1);
}
