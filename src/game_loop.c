/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:45:06 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/25 20:32:31 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <math.h>
#include <stdio.h>

unsigned int get_color(int R, int G, int B)
{
	return (R << 16 | G << 8 | B);
}
void display(t_cub3d *game)
{
	double	wall_size;
	int		i;
	int		wall_top;
	double	dis;
	unsigned int	color;
	double intensity;

	i = 0;
/* 	while (i < RAY_COUNT)
	{
		double temp = (game->player.angle - game->rays[i].angle) * (M_PI / 180.0);
		dis = cos(temp) * game->rays[i].dis;
		intensity = 1.0 - (dis / 700);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;

		unsigned int r, g, b;
			r = (unsigned int)(15 * intensity);
			g = (unsigned int)(210 * intensity);
			b = (unsigned int)(210 * intensity);
		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background,WINDOWS_WIDTH + i, 0, 1, WINDOWS_HEIGHT / 2, false, color);
			r = (unsigned int)(210 * intensity);
			g = (unsigned int)(15 * intensity);
			b = (unsigned int)(67 * intensity);
		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background,WINDOWS_WIDTH + i, WINDOWS_HEIGHT / 2, 1, WINDOWS_HEIGHT / 2, false, color);
		i++;
	} */
	draw_rectangle(game->images.background, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT / 2, false, 0x39487362);
	draw_rectangle(game->images.background, 0, WINDOWS_HEIGHT / 2 , WINDOWS_WIDTH, WINDOWS_HEIGHT / 2, false, 0x34523234);
	i = 0;
	color = 0;
	while (i < RAY_COUNT)
	{
		double angle_diff = (game->player.angle - game->rays[i].angle) * (M_PI / 180.0);
		dis = cos(angle_diff) * game->rays[i].dis;
/* 		if (dis > 10)
			dis = 10; // Uzaklık çok küçükse, bir alt sınır belirleyin
		wall_size = (WINDOWS_HEIGHT / dis); // Duvar yüksekliğini hesaplayın

		if (wall_size > WINDOWS_HEIGHT)
		wall_size = WINDOWS_HEIGHT; // Duvar yüksekliğini ekran yüksekliğiyle sınırlayın
 */
		wall_size = (WINDOWS_HEIGHT / dis);
		if (i > RAY_COUNT - 10)
			printf("%f\n", wall_size);
		if (wall_size > 10)
			wall_size = 10;
		wall_size *= 100;
		wall_top = (WINDOWS_HEIGHT - wall_size) / 2;
		intensity = 1.0 - (dis / 550);
		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;
 		unsigned int r, g, b;
		if (game->rays[i].v_h == 'v')
		{
			r = (unsigned int)(0x29 * intensity);
			g = (unsigned int)(0x68 * intensity);
			b = (unsigned int)(0x00 * intensity);
		}
		else
		{
			r = (unsigned int)(0x00 * intensity);
			g = (unsigned int)(0x45 * intensity);
			b = (unsigned int)(0x31 * intensity);
		}

		color = (r << 16) | (g << 8) | b;
		draw_rectangle(game->images.background, i * (WINDOWS_WIDTH / RAY_COUNT),
			wall_top, (WINDOWS_WIDTH / RAY_COUNT), (int)wall_size, false, color);
		i++;
	}
	printf("\n");
}


void press_move_key(t_cub3d *game, bool key, double rad)
{
	if (key)
	{
		game->player.pos.x += cos(rad) * MOVE_SPEED;
		game->player.pos.y += sin(rad) * MOVE_SPEED;
	}
}

void	update_player_status(t_cub3d *game)
{
	double temp = (game->player.angle) * (M_PI / 180.0);


	if (game->player.is_press_w)
	{
		game->player.pos.x += cos(temp) * MOVE_SPEED;
		game->player.pos.y += sin(temp) * MOVE_SPEED;
	}
	if (game->player.is_press_s)
	{
		game->player.pos.x -= cos(temp) * MOVE_SPEED;
		game->player.pos.y -= sin(temp) * MOVE_SPEED;
	}
	if (game->player.is_press_d)
	{
		game->player.pos.x += cos(temp + M_PI_2) * MOVE_SPEED;
		game->player.pos.y += sin(temp + M_PI_2) * MOVE_SPEED;
	}
	if (game->player.is_press_a)
	{
		game->player.pos.x += cos(temp - M_PI_2) * MOVE_SPEED;
		game->player.pos.y += sin(temp - M_PI_2) * MOVE_SPEED;
	}
	if (game->player.is_press_p_rotation)
	{
		game->player.angle += 1.0;
		if (game->player.angle >= 360)
			game->player.angle -= 360;
	}
	if (game->player.is_press_n_rotation)
	{
		game->player.angle -= 1.0;
		if (game->player.angle < 0)
			game->player.angle += 360;
	}

	if (game->player.pos.y < 11.0)
		game->player.pos.y = 11.0;
	if (game->player.pos.y > game->map.height * REC_HEIGHT - 11.0)
		game->player.pos.y = game->map.height * REC_HEIGHT - 11.0;
	if (game->player.pos.x > game->map.width * REC_WIDTH - 11.0)
		game->player.pos.x = game->map.width * REC_WIDTH - 11.0;
	if (game->player.pos.x < 11.0)
		game->player.pos.x = 11.0;
}

int	game_loop(t_cub3d	*game)
{
	double		horizontal_ray_distance;
	double		vertical_ray_distance;
	t_vec2		horizontal_ray_pos;
	t_vec2		vertical_ray_pos;
	double		i;
	int			a;
	double		rad;
	double		tan_a;

	update_player_status(game);

	i = 0;
	a = 0;

	while (a < RAY_COUNT)
	{
		game->rays[a].angle = game->player.angle + i - (PERSPECTIVE / 2.0);
		if (game->rays[a].angle < 0)
			game->rays[a].angle += 360;
		if (game->rays[a].angle > 360)
			game->rays[a].angle -= 360;
		if (game->rays[a].angle == 45.0 || game->rays[a].angle == 135.0 || game->rays[a].angle == 225.0 || game->rays[a].angle == 315.0)
			game->rays[a].angle += 0.000042;
		rad = game->rays[a].angle * (M_PI / 180.0);
		tan_a = tan(rad);
		horizontal_ray_pos = horizontal_ray_calculator(game, rad, tan_a);
		vertical_ray_pos = vertical_ray_calculator(game, rad, tan_a);
		horizontal_ray_distance = distance(game->player.pos, horizontal_ray_pos);
		vertical_ray_distance = distance(game->player.pos, vertical_ray_pos);
		if (horizontal_ray_distance > vertical_ray_distance)
		{
			game->rays[a].pos = vertical_ray_pos;
			game->rays[a].dis = vertical_ray_distance;
			game->rays[a].v_h = 'v';
		}
		else
		{
			game->rays[a].pos = horizontal_ray_pos;
			game->rays[a].dis = horizontal_ray_distance;
			game->rays[a].v_h = 'h';
		}
		//bresenham_line(game->images.background, (int)game->player.pos.x, (int)game->player.pos.y, (int)game->rays[a].pos.x, (int)game->rays[a].pos.y, 0x00FFFF23);
		i += PERSPECTIVE / RAY_COUNT;
		a++;
	}
	display(game);
	mlx_put_image_to_window(game->mlx, game->win, game->images.background.image, 0, 0);
	return (0);
}

/*	mousenin olduğu kareyi belirlenen renge boyar.
 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDTH * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
