/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:44 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/21 15:57:35 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// typedef t_file
// typedef t_cub3d
// extension_is_cub(char *file_name);
// read_file(char *file_name);
// seperate_content(char *content);
#include "../includes/libft/libft.h"
// ft_strfree(char *str);
#include <fcntl.h>
// O_RDONLY
// open(const char *pathname, int flags);
#include <unistd.h>
// STDERR_FILENO
#include <stdlib.h>
#include <stdio.h>

void	free_file(t_file *file)
{
	if (file->map)
		ft_strfree(file->map);
	if (file->no)
		ft_strfree(file->no);
	if (file->so)
		ft_strfree(file->so);
	if (file->we)
		ft_strfree(file->we);
	if (file->ea)
		ft_strfree(file->ea);
}

static t_file	parse_file(char *file_name)
{
	int		fd;
	char	*line;
	t_file	file;

	if (!extension_is_cub(file_name))
		exit(1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror(ERR_CUB3D);
		exit(1);
	}
	line = read_file(fd);
	close(fd);
	if (!line)
		exit(1);
	file = separate_content(line);
	return (file);
}

static void	process_data(t_cub3d *game, t_file *file)
{
	set_game_map(game, file);
	set_game_player(game);
	if (!initialize_mlx(game))
	{
		ft_strfree(game->map.map);
		free_file(file);
		exit(1);
	}
	game->frame_second = my_system_time();
	game->floor = file->f;
	game->ceiling = file->c;
	set_game_sprites(game, file);
}

void	configure_level(t_cub3d *game, char *file_name)
{
	t_file	file;

	file = parse_file(file_name);
	process_data(game, &file);
	free_file(&file);
}
