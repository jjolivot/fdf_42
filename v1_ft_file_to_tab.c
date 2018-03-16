/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:44:52 by jjolivot          #+#    #+#             */
/*   Updated: 2018/02/21 15:59:09 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

//
//pour chaque line, split dans un tableau
//atoi tout le tableau dans une chaine int
//mettre toute la chaine dans le maillon suivant
//faire une chaine contenant chaque ligne en int *
//mettre toute les strings dans un seul tableau dans info

t_list	*ft_to_list(char *filepath, int *i)
{
	int		fd;
	t_list	*end;
	char	*line;

	end = ft_lstnew(0, 0);
	end->next = NULL;
	fd = open(filepath, O_RDONLY);
	*i = 0;
	while (get_next_line(fd, &line))
	{
		(*i)++;
		ft_lstadd(&end, ft_lstnew(line, ft_strlen(line)));
		free(line);
	}
	return (end);
}

int	ft_list_to_tab(t_coor *info, t_list *end)
{
	char	**tab;
	int		i;
	int		j;

	i = info->i_max;
	while (end->next)
	{
		printf("tab = %p i = %d end->content = %s\n",tab, i, end->content);
		if((tab = ft_strsplit(end->content, ' ')) == NULL)
			return (0);
		printf("marche\n");
		if(!(info->tab[--i] = (int *)malloc(sizeof(int) *
					ft_strlen((const char *)tab))))
		return (0);
		j = -1;
		while (tab[++j] != NULL)
		{
			printf("marche encore i = %d j = %d", i, j);
			info->tab[i][j] = ft_atoi(tab[j]);
			printf(" pas la\n");
		}
		ft_all_free(&tab);
		info->j_max = j;
		free(end->content);
		end = end->next;
	}
	return (1);
}

t_coor	ft_file_to_tab(char *filepath, int line_nbr)
{
	t_coor	info;
	int		i;
	t_list	*end;

	info.zoom = 0;
	end = ft_to_list(filepath, &i);
	if(!(info.tab = (int **)malloc(sizeof(int*) * i)))
			return (info);
	info.i_max = i;
	if (!ft_list_to_tab(&info, end))
		return (info);
	info.zoom = 1;
	info.x_offset = 0;
	info.y_offset = 0;
	info.x_angle = 0;
	info.y_angle = 0;
	info.z_angle = 0;
	return (info);
}

int	main(int argc, char **argv)
{
	t_coor	info;
	int		i;
	int		j;

	argc = 6;
	info = ft_file_to_tab(argv[1]);
	printf("retour au main");
	i = -1;
	j = -1;
	while (++i < info.i_max)
	{
		while (++j < info.j_max)
			printf("%d ", info.tab[i][j]);
		j = -1;
		printf("\n");
	}
	return (1);
}
