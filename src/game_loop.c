/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/12 22:27:56 by bkorkut          ###   ########.fr       */
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

void	ray_throw(t_cub3d *game)
{
	int		dof, mx, my, mp;
	float	aTan, ra, rx, ry, xo, yo;


	ra = game->player.angle * (M_PI / 180);
	aTan = -1/tan(ra);
	if (ra > M_PI) // upper hemisphere
	{
		// rounds the player position to the nearest 100's value.
		ry = (((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT) - 0,0001;
		// takes the difference of y's, finds the x position, offsets it by the player coordinate.
		rx = (game->player.pos.y - ry) * aTan + game->player.pos.x;
		// this gets you the first horizontal line hit with 100's as y value and x value still floatin'.
		yo = -100;
		xo = -yo * aTan;
	}
	else if (ra < M_PI) // lower hemisphere
	{
		// rounds the player position to the nearest 100's value.
		ry = (((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT) + REC_HEIGHT;
		// takes the difference of y's, finds the x position, offsets it by the player coordinate.
		rx = (game->player.pos.y - ry) * aTan + game->player.pos.x;
		// this gets you the first horizontal line hit with 100's as y value and x value still floatin'.
		yo = 100;
		xo = -yo * aTan;
	}
	else if (ra == 0 || ra == M_PI) // looking straight
	{
		ry = game->player.pos.y;
		rx = game->player.pos.x;
		dof = MAP_HEIGHT;
	}
	while (dof < MAP_HEIGHT)
	{
		mx = rx / 100;
		my = ry / 100;
		if (mx * my < MAP_HEIGHT * MAP_WIDHT && game->map.map[my][mx] == 1) // hit a wall?
			dof = MAP_HEIGHT;
		else	// next line
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, rx, ry, 0x0000FF00);
}

void	update_player_status(t_cub3d *game)
{
	if (game->player.is_press_w && game->player.pos.y > 3.0f)
		game->player.pos.y -= 1.0f;
	if (game->player.is_press_s && game->player.pos.y < MAP_HEIGHT * REC_HEIGHT - 3.0f)
		game->player.pos.y += 1.0f;
	if (game->player.is_press_d && game->player.pos.x < MAP_WIDHT * REC_WIDTH - 3.0f)
		game->player.pos.x += 1.0f;
	if (game->player.is_press_a && game->player.pos.x > 3.0f)
		game->player.pos.x -= 1.0f;
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
			game->player.angle = 360;
	}
}

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
/*	mousenin olduğu kareyi belirlenen renge boyar.
 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
	draw_map(game);
	draw_player(game);
	ray_throw(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}
