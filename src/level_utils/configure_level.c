/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:44 by bkorkut           #+#    #+#             */
/*   Updated: 2024/08/08 14:28:14 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
// typedef t_file
// typedef t_cub3d
// extension_is_cub(char *file_name);
// read_file(char *file_name);
// seperate_content(char *content);
#include <fcntl.h>
// O_RDONLY
// open(const char *pathname, int flags);
#include <unistd.h>
// STDERR_FILENO

static t_file parse_file(char *file_name)
{
	int		fd;
	char	*line;
	t_file	file;

	if (!extension_is_cub(file_name))
		exit(1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("cub3d");
		exit(1);
	}
	line = read_file(fd);
	close(fd);
	if (!line)
		exit(1);
	file = seperate_content(line);
	return (file);
}

// void	process_data(t_cub3d *game, t_file *file);

void	configure_level(t_cub3d *game, char *file_name)
{
	t_file	file;

	file = parse_file(file_name);
	process_data(game, file);
}
