/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:04:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/28 18:10:24 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	ft_struct_set(int line_nbr, t_coor *info)
{
	info->i_max = line_nbr;
	if (!(info->tab = (int **)malloc(sizeof(int *) * line_nbr)))
		return (-1);
	info->x_angle = 0;
	info->y_angle = 0;
	info->z_angle = 0;
	info->zoom = 1;
	info->x_offset = 0;
	info->y_offset = 0;
	info->height = 1;
	info->z_min = 2147483647;
	info->z_max = -2147483648;
	return (0);
}

t_coor			ft_error(int err, t_coor info)
{
	if (err == 1)
		ft_putstr("Erreur: lignes de tailles inegales\n");
	info.tab[0][0] = -1;
	return (info);
}

int				ft_file_to_tab_suite(t_coor *info, int (*fd)[4], char ***split)
{
	char *line;

	while (get_next_line((*fd)[0], &line))
	{
		(*fd)[2] = -1;
		(*split) = ft_strsplit(line, ' ');
		if ((*fd)[3] == -1)
			(*fd)[3] = ft_tab_size((*split));
		if ((*fd)[3] != ft_tab_size((*split)))
			return (-1);
		if (!(info->tab[++(*fd)[1]] = (int *)malloc(sizeof(int) *
					ft_tab_size((*split)))))
			return (-1);
		while ((*split)[++(*fd)[2]])
		{
			info->tab[(*fd)[1]][(*fd)[2]] = ft_atoi((*split)[(*fd)[2]]);
			if (info->tab[(*fd)[1]][(*fd)[2]] > info->z_max)
				info->z_max = info->tab[(*fd)[1]][(*fd)[2]];
			if (info->tab[(*fd)[1]][(*fd)[2]] < info->z_min)
				info->z_min = info->tab[(*fd)[1]][(*fd)[2]];
		}
		free(line);
		ft_all_free((*split));
	}
	return ((*fd)[2]);
}

t_coor			ft_file_to_tab(char *filepath, int line_nbr)
{
	t_coor	info;
	int		fd[4];
	char	**split;

	if (ft_struct_set(line_nbr, &info) == -1)
		return (ft_error(0, info));
	fd[0] = open(filepath, O_RDONLY);
	fd[1] = -1;
	fd[3] = -1;
	if (ft_file_to_tab_suite(&info, &fd, &split) == -1)
		return (ft_error(0, info));
	info.j_max = fd[2];
	return (info);
}
