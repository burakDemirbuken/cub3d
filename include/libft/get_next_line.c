/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:04:54 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/06/06 14:46:53 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	read_loop(char **line, int fd)
{
	char	c[2];
	long	bytes_read;
	char	*tmp;
	int		len;

	len = 0;
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, c, 1);
		if (bytes_read == 0)
			return (bytes_read);
		if (bytes_read == -1)
			return (free(*line), -1);
		c[1] = '\0';
		tmp = ft_strjoin(*line, c);
		if (!tmp)
			return (free(*line), -1);
		free(*line);
		*line = tmp;
		len++;
		if (c[0] == '\n')
			return (len);
	}
	return (len);
}

int	get_next_line(int fd, char **line)
{
	int	bytes_read;

	if (fd < 0)
		return (-1);
	*line = ft_strdup("");
	if (!(*line))
		return (-1);
	bytes_read = read_loop(line, fd);
	if (bytes_read == -1)
		return (-1);
	return (bytes_read);
}
