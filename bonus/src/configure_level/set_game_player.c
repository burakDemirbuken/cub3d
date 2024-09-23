/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:22:05 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/23 18:03:23 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
/*
 *	typedef struct s_cub3d t_cub3d
 *	# define NORTH		'N'
 *	# define SOUTH		'S'
 *	# define WEST		'W'
 *	# define EAST		'E'
 *	# define REC_HEIGHT	100
 *	# define REC_WIDTH	100
 */
#include "libft/libft.h"
/*
 *	char *ft_strchr(const char *s, int c)
 */
#include <math.h>
/*
 *	M_PI_2	1.57079632679489661923132169163975144
 *	M_PI 	3.14159265358979323846264338327950288
 */

static void	set_player_angle(t_cub3d *game, int i, int j)
{
	if (game->map.map[i][j] == NORTH)
		game->player.angle = M_PI_2;
	else if (game->map.map[i][j] == EAST)
		game->player.angle = MATH_2PI;
	else if (game->map.map[i][j] == SOUTH)
		game->player.angle = MATH_3PI_2;
	else if (game->map.map[i][j] == WEST)
		game->player.angle = M_PI;
}

void	set_game_player(t_cub3d *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (ft_strchr("NWES", game->map.map[i][j]) != NULL)
			{
				game->player.pos.x = j * REC_WIDTH + (REC_WIDTH / 2);
				game->player.pos.y = i * REC_HEIGHT + (REC_HEIGHT / 2);
				set_player_angle(game, i, j);
				game->map.map[i][j] = '0';
				return ;
			}
		}
	}
}
