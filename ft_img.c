/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 18:41:36 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/23 17:12:23 by jjolivot         ###   ########.fr       */
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
	if (x > 0 && x < WIN_SIZE && y > 0 && y < WIN_SIZE)
	{
		(*img_str)[WIN_SIZE * y * 4 + 4 * x + 0] = (char)(color >> 0 & 0xFF);
		(*img_str)[WIN_SIZE * y * 4 + 4 * x + 1] = (char)(color >> 8 & 0xFF);
		(*img_str)[WIN_SIZE * y * 4 + 4 * x + 2] = (char)(color >> 16 & 0xFF);
	}
}
