/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:00:31 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 21:13:59 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft/libft.h"
// ft_strlen(char *str);
// ft_putstr_fd(char *str, int fd);
// ft_strdup(char *str);
// ft_strjoin(char *str1, char *str2);
#include "../../includes/cub3d.h"
// <stdbool.h>
// |-->	bool _Bool
#include <fcntl.h>
// O_RDONLY
// open(const char *pathname, int flags);
#include <unistd.h>
// STDERR_FILENO
#include <stdio.h>
// perror(const char *)

bool	extension_is_cub(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len <= 4 || file_name[--len] != 'b' || file_name[--len] != 'u'
		|| file_name[--len] != 'c' || file_name[--len] != '.')
		return (ft_putstr_fd(ERR_FEXT, STDERR_FILENO), false);
	return (true);
}

bool	the_path_is_valid(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (perror(ERR_CUB3D), false);
	close(fd);
	return (true);
}

char	*read_file(int fd)
{
	int		bytes;
	char	buffer[2];
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	if (line == NULL)
		return (perror(ERR_CUB3D), NULL);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, 1);
		if (bytes == -1)
			return (perror(ERR_CUB3D), free(line), NULL);
		if (bytes == 0 && !line)
			return (ft_putstr_fd(ERR_FEMT, STDERR_FILENO), NULL);
		buffer[1] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		if (tmp == NULL)
			return (perror(ERR_CUB3D), NULL);
		line = tmp;
	}
	return (line);
}
