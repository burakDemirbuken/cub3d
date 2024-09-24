/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:44 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/24 10:18:33 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
// typedef t_file
// typedef t_cub3d
// ERR_CUB3D "cub3D"
// extension_is_cub(char *file_name);
// read_file(char *file_name);
// seperate_content(char *content);
// set_game_map(t_cub3d *game, t_file *file)
// set_game_player(t_cub3d *game)
// initialize_mlx(t_cub3d *game)
// my_system_time(void)
// set_game_sprites(t_cub3d *game, t_file *file)
// free_file(t_file *file)
#include "libft/libft.h"
// ft_strfree(char *str);
#include <fcntl.h>
// O_RDONLY
// open(const char *pathname, int flags);
#include <unistd.h>
// close(int)
#include <stdlib.h>
// exit(int)
#include <stdio.h>
// perror(const char *)

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
