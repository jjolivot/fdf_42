/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjolivot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 18:54:48 by jjolivot          #+#    #+#             */
/*   Updated: 2018/02/02 22:48:14 by jjolivot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_get_reste(char **reste, char **line)
{
	char		*endline;
	char		*tmp;

	if ((endline = ft_strchr(*reste, '\n')))
	{
		if (!((*line = ft_strsub(*reste, 0, endline - *reste)) &&
		(tmp = ft_strsub(*reste, endline - *reste + 1, ft_strlen(*reste)))))
			return (-1);
		ft_strdel(reste);
		*reste = tmp;
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(*reste)))
			return (-1);
		ft_strdel(reste);
	}
	return (0);
}

int		ft_gnl_start(int fd, char **line, char **endline, char **reste)
{
	int ret;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	*endline = NULL;
	if (*reste)
	{
		if ((ret = ft_get_reste(reste, &(*line))) == -1)
			return (-1);
		if (ret == 1)
			return (1);
	}
	return (2);
}

int		ft_line(char **line, char (*buff)[BUFF_SIZE + 1], char **r, char **end)
{
	char *tmp;

	if (!((*line = ft_f_strjoin(*line,
		(tmp = ft_strsub(*buff, 0, *end - *buff)))) &&
		(*r = ft_strsub(*buff, *end - *buff + 1, ft_strlen(*buff) -
						(*end - *buff + 1)))))
		return (-1);
	else
		free(tmp);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*reste;
	int			ret;
	char		buff[BUFF_SIZE + 1];
	char		*endline;

	if ((ret = ft_gnl_start(fd, line, &endline, &reste)) != 2)
		return (ret);
	while (!endline)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret == 0 && (*line)[0])
			return (1);
		if (ret == 0 || ret == -1)
			return (ret);
		buff[ret] = '\0';
		if (!(endline = ft_strchr(buff, '\n')))
		{
			if (!(*line = ft_f_strjoin(*line, buff)))
				return (-1);
		}
		else if (ft_line(line, &buff, &reste, &endline) == -1)
			return (-1);
	}
	return (1);
}
