/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:04:31 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/16 17:58:56 by jjolivot         ###   ########.fr       */
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

int	ft_key_hook()
{
	printf("testtest\n");
return (0);
}

void	ft_coor_test(t_coor info)
{
	int i = -1;
	int j = -1;
	int point[2];
	while(++i < 50)
	{
		ft_get_coor(info, 20, i, &point);
	//	printf("point[0] = %d     point [1] = %d\n", point[0], point[1]);
	}

}

int	main(int argc, char **argv)
{
	t_id	id;
	t_coor	info;
	int		ret;

	if ((ret = ft_parsing(argc, argv)) == -1)
		return (-1);
	info = ft_file_to_tab(argv[1], ret);
	id.sess = mlx_init();
	id.win = mlx_new_window(id.sess, WIN_SIZE, WIN_SIZE, "fdf");
	id.img = ft_new_img(WIN_SIZE, WIN_SIZE, id.sess, &id.img_str);
	ft_put_template(id);
	ft_draw_map(info, id);

//	ft_coor_test(info);

	mlx_put_image_to_window(id.sess, id.win, id.img, 0, 0);
	mlx_key_hook(id.win, ft_key_hook, &info);
	mlx_loop(id.sess);
	printf("test\n");
	return (1);
}
