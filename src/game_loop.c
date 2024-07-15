/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/15 15:37:32 by bdemirbu         ###   ########.fr       */
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
		game->player.angle += 2.5F;
		if (game->player.angle > 359)
			game->player.angle = 0;
	}
	if (game->player.is_press_n_totation)
	{
		game->player.angle -= 2.5F;
		if (game->player.angle < 0)
			game->player.angle = 359;
	}
}

int	game_loop(t_cub3d	*game)
{
	float	horizontal_ray_distance;
	float	vertical_ray_distance;
	t_vec2	ray_point;

	update_player_status(game);
	draw_map(game);
	draw_player(game);
	printf("%f\n", game->player.angle);
	for (float i = 0; i <360; i += 0.1f)
	{

		float angle = game->player.angle + i - 30;
		if (angle < 0)
			angle += 360;
		if (angle > 360)
			angle -= 360;
		game->y_one_ray = y_ray_calculator(game, angle);
		game->x_one_ray = x_ray_calculator(game, angle);
		printf("angle: %f\nh_x:%f - h_y: %f \n", angle, game->y_one_ray.x, game->y_one_ray.y);
		printf("x_x:%f - x_y: %f \n", game->x_one_ray.x, game->x_one_ray.y);
		printf("\n");
		horizontal_ray_distance = distance(game->player.pos, game->y_one_ray);
		vertical_ray_distance = distance(game->player.pos, game->x_one_ray);
		if (horizontal_ray_distance > vertical_ray_distance)
			ray_point = game->x_one_ray;
		else
			ray_point = game->y_one_ray;
		bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, (int)ray_point.x, (int)ray_point.y, 0x00FFFF23);
	}
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
