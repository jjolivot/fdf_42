/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:13:24 by jjolivot          #+#    #+#             */
/*   Updated: 2018/03/27 18:32:29 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_line_parsing(char *line)
{
	int i;

	i = -1;
	while (line[++i])
		if (line[i] != 32 && line[i] != '-' && (line[i] > 57 || line[i] < 48))
		{
			ft_putstr("Erreur: le fichier ne doit contenir que des espaces");
			ft_putstr(" et des chiffres\n");
			return (-1);
		}
	return (0);
}

int	ft_argvc_parsing(int argc, char **argv)
{
	if (argc > 2)
		ft_putstr("Erreur: un seul fichier a la fois.\n");
	if (argc > 2)
		return (-1);
	if (argc == 1)
		ft_putstr("Erreur: besoin du chemin d'un fichier en argument\n");
	if (argc == 1)
		return (-1);
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".fdf"))
		ft_putstr("Erreur: le fichier doit etre au forrmat fdf\n");
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".fdf"))
		return (-1);
	return (0);
}

int	ft_parsing(int argc, char **argv)
{
	int		line_nbr;
	int		fd;
	char	*line;

	if (ft_argvc_parsing(argc, argv) == -1)
		return (-1);
	line_nbr = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line))
	{
		line_nbr++;
		if (ft_line_parsing(line) == -1)
			return (-1);
		free(line);
		if (line_nbr > 99999999)
			return (-1);
	}
	free(line);
	return (line_nbr);
}
