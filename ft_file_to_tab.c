/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/23 16:10:34 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
//pour chaque line, split dans un tableau
//atoi tout le tableau dans une chaine int
//mettre toute la chaine dans le maillon suivant
//faire une chaine contenant chaque ligne en int *
//mettre toute les strings dans un seul tableau dans info

static	void	ft_struct_set(int line_nbr, t_coor *info)
{

	info->i_max = line_nbr;
	info->tab = (int **)malloc(sizeof(int *) * line_nbr);
	info->x_angle = 0;
	info->y_angle = 0;
	info->z_angle = 0;
	info->zoom = 1;
	info->x_offset = 0;
	info->y_offset = 0;
	info->height = 1;
	info->z_min = 2147483647;
	info->z_max = -2147483648;
}

//i = lignes, j = colonnes

t_coor ft_error(int err, t_coor info)
{
	if (err == 1)
		ft_putstr("Erreur: lignes de tailles inegales\n");
	info.tab[0][0] = -1;
	return (info);
}

t_coor	ft_file_to_tab(char *filepath, int line_nbr)
{
	t_coor	info;
	int		fd[4];
	char	*line;
	char	**split;

	ft_struct_set(line_nbr, &info);
	fd[0] = open(filepath, O_RDONLY);
	fd[1] = -1;
	fd[3] = -1;
	while(get_next_line(fd[0], &line))
	{
		fd[2] = -1;
		split = ft_strsplit(line, ' ');
		if (fd[3] == -1)
			fd[3] = ft_tab_size(split);
		if (fd[3] != ft_tab_size(split))
			return(ft_error(1, info));
		info.tab[++fd[1]] = (int *)malloc(sizeof(int) * ft_tab_size(split));
		while(split[++fd[2]])
		{
			info.tab[fd[1]][fd[2]] = ft_atoi(split[fd[2]]);
			if (info.tab[fd[1]][fd[2]] > info.z_max)
				info.z_max = info.tab[fd[1]][fd[2]];
			if (info.tab[fd[1]][fd[2]] < info.z_min)
				info.z_min = info.tab[fd[1]][fd[2]];
		}
		free(line);
		ft_all_free(split);
	}
	info.j_max = fd[2];
	return (info);
}
