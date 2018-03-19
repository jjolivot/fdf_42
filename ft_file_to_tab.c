/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/19 19:19:12 by jjolivot         ###   ########.fr       */
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
}

//i = lignes, j = colonnes

t_coor	ft_file_to_tab(char *filepath, int line_nbr)
{
	t_coor	info;
	int		fd[3];
	char	*line;
	char	**split;

	ft_struct_set(line_nbr, &info);
	fd[0] = open(filepath, O_RDONLY);
	fd[1] = -1;
	while(get_next_line(fd[0], &line))
	{
		fd[2] = -1;
		split = ft_strsplit(line, ' ');
		info.tab[++fd[1]] = (int *)malloc(sizeof(int) * ft_tab_size(split));
		while(split[++fd[2]])
			info.tab[fd[1]][fd[2]] = ft_atoi(split[fd[2]]);
		free(line);
		ft_all_free(split);
	}
	info.j_max = fd[2];
	return (info);
}
/*
int		ft_parsing(int argc, char **argv)
{
	int		line_nbr;
	int		fd;
	char	*line;

	line_nbr = 0;
	argc = 9;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		line_nbr++;
		free(line);
	}
	return (line_nbr);
}


int	main(int argc, char **argv)
{
	t_coor	info;
	int		i;
	int		j;
	int		line_nbr;

	line_nbr = ft_parsing(argc, argv);
	info = ft_file_to_tab(argv[1], line_nbr);
	printf("retour au main\ninfo.i_max = %d      info.j_max = %d\n", info.i_max, info.j_max);
	i = -1;
	j = -1;
	while (++i < info.i_max)
	{
		while (++j < info.j_max)
			printf("%d ", info.tab[i][j]);
		j = -1;
		printf("\n");
	}
	while (1);
	return (1);
}*/
