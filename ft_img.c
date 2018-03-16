/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 18:41:36 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/12 19:45:11 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_new_img(int size_line, int line_nbr, void *sess, char **img_string)
{
	void	*ptr_img;
	int		bpp;
	int		s_l;
	int		endian;

	ptr_img = mlx_new_image(sess, size_line, line_nbr);
	*img_string = mlx_get_data_addr(ptr_img, &bpp, &s_l, &endian);
	return (ptr_img);
}

void	ft_fill_pixel(char **img_str, int x, int y, int color)
{
	(*img_str)[WIN_SIZE * y * 4 + 4 * x + 0] = (char)(color >> 0 & 0xFF);
	(*img_str)[WIN_SIZE * y * 4 + 4 * x + 1] = (char)(color >> 8 & 0xFF);
	(*img_str)[WIN_SIZE * y * 4 + 4 * x + 2] = (char)(color >> 16 & 0xFF);
}
/*
int main()
{
	char *img_str;

	void *sess_id = mlx_init();
	void *win_id = mlx_new_window(sess_id, WIN_SIZE, WIN_SIZE, "mlx 42");
	void *img_id = ft_new_img(WIN_SIZE, WIN_SIZE, sess_id, &img_str);
	int i = -1;
	int j = 450;
	while (i++ < 550)
	{
		j = -1;
		while (j++ < 550)
			ft_fill_pixel(&img_str, i, j, 0xFFd700);
	}
	mlx_put_image_to_window(sess_id, win_id, img_id, 0, 0);
	printf("test\n");
	mlx_loop(sess_id);
	return (1);
}*/
