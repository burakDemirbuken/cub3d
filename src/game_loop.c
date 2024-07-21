/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/21 18:00:47 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <math.h>
#include <stdio.h>

void	display(t_cub3d *game)
{
	float	wall_height;
	int		i;
	int		wall_bottom;
	int		wall_top;
	float	dis;
	int		color;

	i = 0;
	draw_rectangle(game->images.background, MAP_WIDHT * REC_WIDTH, 0, REC_WIDTH * MAP_WIDHT, REC_HEIGHT * MAP_HEIGHT, false, 0x00000000);
    while (i < RAY_COUNT)
    {
		dis = game->rays[i].dis;
        wall_height = (MAP_HEIGHT * REC_HEIGHT / dis);
		if (wall_height > 10)
			wall_height = 10;
		wall_height *= 100;
        wall_top = (MAP_HEIGHT * REC_HEIGHT / 2) - (wall_height / 2);
        wall_bottom = wall_top + wall_height;
		if (game->rays[i].v_h == 'v')
			color = 0x00296800;
		else
			color = 0x00004531;
		bresenham_line(game->images.background, REC_WIDTH * MAP_WIDHT + i, wall_top,
												REC_WIDTH * MAP_WIDHT + i, wall_bottom, color);
		i++;
	}
}

void	update_player_status(t_cub3d *game)
{
	if (game->player.is_press_w && game->player.pos.y > 3.0f)
		game->player.pos.y -= 3.0f;
	if (game->player.is_press_s && game->player.pos.y < MAP_HEIGHT * REC_HEIGHT - 3.0f)
		game->player.pos.y += 3.0f;
	if (game->player.is_press_d && game->player.pos.x < MAP_WIDHT * REC_WIDTH - 3.0f)
		game->player.pos.x += 3.0f;
	if (game->player.is_press_a && game->player.pos.x > 3.0f)
		game->player.pos.x -= 3.0f;
	if (game->player.is_press_p_totation)
	{
		game->player.angle += 1.0F;
		if (game->player.angle > 360)
			game->player.angle = 0;
	}
	if (game->player.is_press_n_totation)
	{
		game->player.angle -= 1.0F;
		if (game->player.angle < 0)
			game->player.angle = 359.9999999f;
	}
}

int	game_loop(t_cub3d	*game)
{
	float	horizontal_ray_distance;
	float	vertical_ray_distance;
	float	i;
	int		a;

	update_player_status(game);
	draw_map(game);

	i = 0;
	a = 0;
	while (i <= PERSPECTIVE)
	{
		game->rays[a].angle = game->player.angle + i - (PERSPECTIVE / 2.0f);
		if (game->rays[a].angle < 0)
			game->rays[a].angle += 360;
		if (game->rays[a].angle > 360)
			game->rays[a].angle -= 360;
		if (game->rays[a].angle == 45.0f)
			game->rays[a].angle += 0.000042f;
		game->horizontal_one_ray = horizontal_ray_calculator(game, game->rays[a].angle);
		game->vertical_one_ray = vertical_ray_calculator(game, game->rays[a].angle);
		horizontal_ray_distance = distance(game->player.pos, game->horizontal_one_ray);
		vertical_ray_distance = distance(game->player.pos, game->vertical_one_ray);
		if (horizontal_ray_distance > vertical_ray_distance)
		{
			game->rays[a].pos = game->vertical_one_ray;
			game->rays[a].dis = vertical_ray_distance;
			game->rays[a].v_h = 'v';
		}
		else
		{
			game->rays[a].pos = game->horizontal_one_ray;
			game->rays[a].dis = horizontal_ray_distance;
			game->rays[a].v_h = 'h';
		}
		bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, (int)game->rays[a].pos.x, (int)game->rays[a].pos.y, 0x00FFFF23);
		i += PERSPECTIVE / RAY_COUNT;
		if (a < RAY_COUNT - 1)
			a++;
	}
	display(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}

/*	mousenin olduğu kareyi belirlenen renge boyar.
 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
