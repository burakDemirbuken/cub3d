/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/08 00:14:01 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
	#include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
	#include "../include/minilibx/mlx.h"
#endif
#include <stdio.h>

// include
void	clear_map(t_cub3d *game);

// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
#define REC_HEIGHT	10
#define REC_WIDTH	10

// haritanın uzunluğu ve genişliği
#define MAP_HEIGHT	100
#define MAP_WIDHT	100

// tuşa basıldığı anda t_cub3d structda bulunun değerleri true yapıyor. Bu sayede tuşa basılı tuttuğunu anlaşılıyor.
static int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_totation = 1;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_totation = 1;
	if (keycode == KEY_W)
		game->player.is_press_w = 1;
	if (keycode == KEY_A)
		game->player.is_press_a = 1;
	if (keycode == KEY_S)
		game->player.is_press_s = 1;
	if (keycode == KEY_D)
		game->player.is_press_d = 1;
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_C)
		clear_map(game);
	return (0);
}

// tuşa bıraktığı anda t_cub3d structda bulunun değerleri false yapıyor. Bu sayede tuşa basılı tuttuğunu anlaşılıyor.
static int	key_up(int keycode, t_cub3d *game)
{
	if (keycode == KEY_LEFT)
		game->player.is_press_n_totation = 0;
	if (keycode == KEY_RIGHT)
		game->player.is_press_p_totation = 0;
	if (keycode == KEY_W)
		game->player.is_press_w = 0;
	if (keycode == KEY_A)
		game->player.is_press_a = 0;
	if (keycode == KEY_S)
		game->player.is_press_s = 0;
	if (keycode == KEY_D)
		game->player.is_press_d = 0;
	return (0);
}

// pencerede verilen kordinata genişliği ve yüksekliği bir dikdörtgen çizer.
void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < height)
	{
		i_w = 0;
		while (i_w < width)
		{
			if (!(i_w == width - 1 || i_w == 0
				|| i_h == height - 1 || i_h == 0))
				*(unsigned int*)(game->addr.canvas
				+ (int)((y + i_h) * game->addr.line_lenght
				+		(x + i_w) * (game->addr.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
}

// haritanın renglerini sıfırlar
void	clear_map(t_cub3d *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDHT)
		{
			game->map.map[y][x] = 0x00252525;
			x++;
		}
		y++;
	}
	game->is_click = false;
}

// verilen x0,y0 kordinatından x1 y1 kordinatına doğru bir çizgi çeker.
void	bresenham_line(t_cub3d *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx, dy, p, x, y;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	x = x0;
	y = y0;

	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;

	if (dx > dy)
	{
		p = 2 * dy - dx;
		while (x != x1)
		{
			color = game->map.map[y][x] = 0x000000FF;
			x += sx;
			if (p > 0)
			{
				y += sy;
				p -= 2 * dx;
			}
			p += 2 * dy;
		}
	}
	else
	{
		p = 2 * dx - dy;
		while (y != y1)
		{
			color = game->map.map[y][x] = 0x00FF0000;
			y += sy;
			if (p > 0)
			{
				x += sx;
				p -= 2 * dy;
			}
			p += 2 * dx;
		}
	}
	game->map.map[y1][x1] = color;
}

// haritada bulunacak dikdörtgenleri çizer
void	draw_map(t_cub3d *game)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, game->map.map[y][x]);
			x++;
		}
		y++;
	}
}

int	game_loop(t_cub3d	*game)
{
	int	x;
	int	y;

	// eğer tusa basılıysa değerleri artırır.
	if (game->player.is_press_w)
		game->player.pos.y -= 1.5f;
	if (game->player.is_press_s)
		game->player.pos.y += 1.5f;
	if (game->player.is_press_d)
		game->player.pos.x += 1.5f;
	if (game->player.is_press_a)
		game->player.pos.x -= 1.5f;
	if (game->player.is_press_p_totation)
	{
		game->player.angle += 1.5F;
		if (game->player.angle == 361)
			game->player.angle = 0;
	}
	if (game->player.is_press_n_totation)
	{
		game->player.angle -= 1.5F;
		if (game->player.angle == -1)
			game->player.angle = 360;
	}

	draw_map(game);
	// mousenin olduğu kareyi farklı renge boyar.
	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, 0x00808080);
	mlx_put_image_to_window(game->mlx, game->win, game->background, 0, 0);
	return (0);
}

// ilk tıklamada bir kare seçer ikinci tıklamada ise 1. tıklamayla 2. tıklama arasına çizgi çeker.
int	mouse_click(int keycode, int x, int y, t_cub3d *game)
{
	if (keycode == 1)
	{
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDHT * REC_WIDTH))
		{
			if (game->is_click == false)
			{
				game->is_click = true;
				game->click.y = y / REC_HEIGHT;
				game->click.x = x / REC_WIDTH;
				game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x0000FF00;
			}
			else
			{
				game->is_click = false;
				bresenham_line(game, game->click.x, game->click.y, x / REC_WIDTH, y / REC_HEIGHT, 0x00202020);
			}
		}
	}
	if (keycode == 2)
		if (!(x < 0 || y > MAP_HEIGHT * REC_HEIGHT || y < 0 || x > MAP_WIDHT * REC_WIDTH))
			game->map.map[y / REC_HEIGHT][x / REC_WIDTH] = 0x00252525;
	return (0);
}

// haritayı verilen genişliğe ve uzunluğa göre oluşturur
// pencere oluşturup oyunu başlatır.
int	main()
{
	t_cub3d	game;
	int		y;
	int		x;

	ft_memset(&game, 0, sizeof(t_cub3d));

	game.map.map = (unsigned int **)malloc(sizeof(unsigned int *) * (MAP_HEIGHT + 1));
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		game.map.map[y] = (unsigned int *)malloc(sizeof(unsigned int) * (MAP_WIDHT + 1));
		while (x < MAP_WIDHT)
		{
			game.map.map[y][x] = 0x00252525;
			x++;
		}
		game.map.map[y][x] = 0;
		y++;
	}
	game.map.map[y] = 0;

	game.mlx = mlx_init();
	if (!game.mlx)
		exit(0);
	game.win = mlx_new_window(game.mlx, MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT, "naber müdür");
	if (!game.win)
		exit(0);
	game.background = mlx_new_image(game.mlx,  MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT);
	game.addr.canvas = mlx_get_data_addr(game.background, &game.addr.bits_per_pixel, &game.addr.line_lenght, &game.addr.endian);
	draw_map(&game);


/* 	int is, ys;
	game.icon = mlx_xpm_file_to_image(game.mlx, "./icon.xpm", &is, &ys);
 */
	mlx_hook(game.win, 3, 1L << 0, key_up, &game);
	mlx_hook(game.win, 2, 1L << 1, key_down, &game);
	mlx_mouse_hook(game.win, mouse_click, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

