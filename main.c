/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:04:31 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/19 23:49:42 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	ft_line_parsing(char *line)
{
return (0);
}

int		ft_parsing(int argc, char **argv)
{
	int		line_nbr;
	int		fd;
	char	*line;

	line_nbr = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		line_nbr++;
		if (ft_line_parsing(line) == -1)
			return (-1);
		free(line);
	}
	return (line_nbr);
}

void	ft_put_template(t_id id)
{

}

int	ft_loop_hook(t_coor *info)
{
	ft_draw_map(*info, *(*info).id);
	mlx_put_image_to_window(info->id->sess, info->id->win, info->id->img, 0, 0);
	ft_bzero(info->id->img_str, (WIN_SIZE * WIN_SIZE * 4));
	mlx_put_image_to_window(info->id->sess, info->id->win, info->id->img, 0, 0);
	ft_draw_map(*info, *info->id);

	return (0);
}

int	ft_key_hook(int kc, t_coor *info)
{
//haut
	if (kc == 126)
		info->x_angle = info->x_angle + 3;
//bas
	if (kc == 125)
		info->x_angle = info->x_angle - 3;
//gauche
	if (kc == 123)
		info->y_angle = info->y_angle + 3;
//droite
	if (kc == 124)
		info->y_angle = info->y_angle - 3;
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
	printf("touche = %d\n info z angle = %f\n", kc, info->z_angle);
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
	id.sess = mlx_init();
	id.win = mlx_new_window(id.sess, WIN_SIZE, WIN_SIZE, "fdf");
	id.img = ft_new_img(WIN_SIZE, WIN_SIZE, id.sess, &id.img_str);
	ft_put_template(id);
	ft_draw_map(info, id);
	info.id = &id;
	mlx_hook(id.win, 2, (1l << 8), &ft_key_hook, &info);
	mlx_loop_hook(id.sess, &ft_loop_hook, &info);
	mlx_loop(id.sess);
	return (1);
}
