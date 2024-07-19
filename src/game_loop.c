/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/19 16:30:24 by bkorkut          ###   ########.fr       */
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
		game->player.pos.y -= 2.0f;
	if (game->player.is_press_s && game->player.pos.y < MAP_HEIGHT * REC_HEIGHT - 3.0f)
		game->player.pos.y += 2.0f;
	if (game->player.is_press_d && game->player.pos.x < MAP_WIDHT * REC_WIDTH - 3.0f)
		game->player.pos.x += 2.0f;
	if (game->player.is_press_a && game->player.pos.x > 3.0f)
		game->player.pos.x -= 2.0f;
	if (game->player.is_press_r_totation)
	{
		game->player.angle += 2.0F;
		if (game->player.angle > 360)
			game->player.angle = 0;
	}
	if (game->player.is_press_l_totation)
	{
		game->player.angle -= 2.0F;
		if (game->player.angle < 0)
			game->player.angle = 360;
	}
}

float	dist(float px, float py, float rx, float ry, float ang)
{
	return(sqrt(((rx - px) * (rx - px)) + ((ry - py) * (ry - py))));
}

void	ray_throw(t_cub3d *game)
{
	// check horizontal lines
	int		dof, mx, my, mp;
	float	ray_ang, rx, ry, xo, yo;
	ray_ang = (game->player.angle * RADIANS) - (RADIANS * 30);

	if (ray_ang < 0)
		ray_ang += (2 * M_PI);
	if (ray_ang > (2 * M_PI))
		ray_ang -= (2 * M_PI);
	for (float r = 0; r < 60; r++)
	{
		dof = 0;
		float distH = 10000000.f, hx=game->player.pos.x, hy=game->player.pos.y;
		float aTan = -1/tan(ray_ang);
		if (ray_ang > M_PI) // looking down (logically)
		{
			ry = (((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT) - 0.0001;
			rx = (game->player.pos.y - ry) * aTan + game->player.pos.x;
			yo = -100;
			xo = -yo * aTan;
		}
		else if (ray_ang < M_PI) // looking up (logically)
		{
			ry = (((int)game->player.pos.y / REC_HEIGHT) * REC_HEIGHT) + REC_HEIGHT;
			rx = (game->player.pos.y - ry) * aTan + game->player.pos.x;
			yo = 100;
			xo = -yo * aTan;
		}
		else if (ray_ang == 0 || ray_ang == M_PI) // looking straight
		{
			ry = game->player.pos.y;
			rx = game->player.pos.x;
			dof = MAP_HEIGHT;
		}
		while (dof < MAP_HEIGHT)
		{
			mx = rx / REC_WIDTH;
			my = ry / REC_HEIGHT;
			if (my < MAP_HEIGHT && my >= 0 && mx < MAP_WIDHT && mx >= 0
				&& game->map.map[my][mx] == '1') // hit a wall?
			{
				hx = rx;
				hy = ry;
				distH = dist(game->player.pos.x, game->player.pos.y, hx, hy, ray_ang);
				// printf("horizontal hit\n");
				dof = MAP_HEIGHT;
			}
			else	// next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		// check vertical lines
		dof = 0;
		float distV = 10000000.f, vx = game->player.pos.x, vy = game->player.pos.y;
		float nTan = -tan(ray_ang);
		if (ray_ang > M_PI_2 && ray_ang < M_PI + M_PI_2) // looking left
		{
			rx = (((int)game->player.pos.x / REC_HEIGHT) * REC_HEIGHT) - 0.0001;
			ry = (game->player.pos.x - rx) * nTan + game->player.pos.y;
			xo = -100;
			yo = -xo * nTan;
		}
		else if (ray_ang < M_PI_2 || ray_ang > M_PI + M_PI_2) // looking right
		{
			rx = (((int)game->player.pos.x / REC_HEIGHT) * REC_HEIGHT) + REC_HEIGHT;
			ry = (game->player.pos.x - rx) * nTan + game->player.pos.y;
			xo = 100;
			yo = -xo * nTan;
		}
		else if (ray_ang == 0 || ray_ang == M_PI) // looking straight
		{
			ry = game->player.pos.y;
			rx = game->player.pos.x;
			dof = MAP_HEIGHT;
		}
		while (dof < MAP_HEIGHT)
		{
			mx = rx / REC_WIDTH;
			my = ry / REC_HEIGHT;
			if (my < MAP_HEIGHT && my >= 0 && mx < MAP_WIDHT && mx >= 0
				&& game->map.map[my][mx] == '1') // hit a wall?
			{
				vx = rx;
				vy = ry;
				distV = dist(game->player.pos.x, game->player.pos.y, vx, vy, ray_ang);
				// printf("vertical hit\n");
				dof = MAP_HEIGHT;
			}
			else	// next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		if (distV < distH)
		{
			rx = vx;
			ry = vy;
		}
		else
		{
			rx = hx;
			ry = hy;
		}
		// printf("px: %f py:%f\n", game->player.pos.x, game->player.pos.y);
		// printf("hx: %f hy:%f\n", hx, hy);
		// printf("vx: %f vy:%f\n", vx, vy);
		// printf("vd: %f hd:%f\n", distV, distH);
		// bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, hx, hy, 0x00FF0000);
		// bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, vx, vy, 0x0000FF00);
		bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, rx, ry, 0x000000FF);
		ray_ang += RADIANS;
		if (ray_ang < 0)
			ray_ang += (2 * M_PI);
		if (ray_ang > (2 * M_PI))
			ray_ang -= (2 * M_PI);
	}
}

int	game_loop(t_cub3d	*game)
{
	update_player_status(game);
	draw_map(game);
	draw_player(game);
	ray_throw(game);
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
