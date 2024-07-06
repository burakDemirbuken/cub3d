/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/06 18:45:28 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include "../include/minilibx/mlx.h"
#include <stdio.h>

void	clear_map(t_cub3d *game);

#define REC_HEIGHT	10
#define REC_WIDTH	10
#define MAP_HEIGHT	100
#define MAP_WIDHT	100

static int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 123)
		game->player.is_press_n_totation = 1;
	if (keycode == 124)
		game->player.is_press_p_totation = 1;
	if (keycode == 13)
		game->player.is_press_w = 1;
	if (keycode == 0)
		game->player.is_press_a = 1;
	if (keycode == 1)
		game->player.is_press_s = 1;
	if (keycode == 2)
		game->player.is_press_d = 1;
	if (keycode == 8)
		clear_map(game);
	return (0);
}

static int	key_up(int keycode, t_cub3d *game)
{
	if (keycode == 123)
		game->player.is_press_n_totation = 0;
	if (keycode == 124)
		game->player.is_press_p_totation = 0;
	if (keycode == 13)
		game->player.is_press_w = 0;
	if (keycode == 0)
		game->player.is_press_a = 0;
	if (keycode == 1)
		game->player.is_press_s = 0;
	if (keycode == 2)
		game->player.is_press_d = 0;
	return (0);
}

void	draw_rectangle(t_cub3d *game, int x, int y, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < REC_HEIGHT)
	{
		i_w = 0;
		while (i_w < REC_WIDTH)
		{
			if (!(i_w == REC_WIDTH - 1 || i_w == 0
				|| i_h == REC_HEIGHT - 1 || i_h == 0))
				*(unsigned int*)(game->addr.canvas
				+ (int)((y + i_h) * game->addr.line_lenght
				+		(x + i_w) * (game->addr.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
}

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
}

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
	else if (dx == dy)
	{
		p = 2 * dx - dy;
		while (y != y1)
		{
			color = game->map.map[y][x] = 0x00FF00FF;
			y += sy;
			if (p > 0)
			{
				x += sx;
				p -= 2 * dy;
			}
			p += 2 * dx;
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
			draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, game->map.map[y][x]);
			x++;
		}
		y++;
	}
}
#include <math.h>

void	*rotate_image(t_cub3d *game, void *mlx, void *img, int width, int height, double angle)
{
    int     x;
    int     y;
    int     new_x;
    int     new_y;
    int     color;
    double  rad_angle;
    void    *new_img;
    int     *data;
    int     *new_data;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
    // Açıları radyana çevir
    rad_angle = angle * M_PI / 180.0;
    // Yeni resim oluştur
    new_img = mlx_new_image(mlx, width, height);
    new_data = (int *)mlx_get_data_addr(new_img, &bits_per_pixel, &size_line, &endian);
    data = (int *)mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            // Pikselin yeni konumunu hesapla
            new_x = (int)(cos(rad_angle) * (x - width / 2) - sin(rad_angle) * (y - height / 2) + width / 2);
            new_y = (int)(sin(rad_angle) * (x - width / 2) + cos(rad_angle) * (y - height / 2) + height / 2);
            // Yeni konum geçerli bir pozisyonda mı kontrol et
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
            {
                color = data[y * width + x];
                new_data[new_y * width + new_x] = color;
            }
        }
    }
	return (new_img);
}

int	game_loop(t_cub3d	*game)
{
/* 	if (game->player.is_press_w)
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
	} */
	int	x,y;
	draw_map(game);
	mlx_mouse_get_pos(game->win, &x, &y);
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, 0x00808080);
	mlx_put_image_to_window(game->mlx, game->win, game->background, 0, 0);
	return (0);
}

/* typedef struct  s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

int main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x = 100;
    int     y = 100;
    int     color = 0x00FF0000; // Kırmızı

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
    img.img = mlx_new_image(mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Pikseli ayarla
    char *pixel;
    pixel = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
    *(unsigned int*)pixel = color;

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);

    return 0;
}

 */
/*
unsigned int get_pixel_color(t_cub3d *data, int x, int y)
{
    char *src;

    src = data->addr + (y * data->addr.line_lenght + x * (data->addr.bits_per_pixel / 8));
    return (*(unsigned int*)src);
}

void rotate_image(t_data *src, t_data *dst, int width, int height, double angle)
{
    int cx = width / 2;
    int cy = height / 2;
    double rad = angle * M_PI / 180.0;
    int x, y;
    int new_x, new_y;
    unsigned int color;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            new_x = (int)((x - cx) * cos(rad) - (y - cy) * sin(rad) + cx);
            new_y = (int)((x - cx) * sin(rad) + (y - cy) * cos(rad) + cy);
            if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height)
            {
                color = get_pixel_color(src, x, y);
                my_mlx_pixel_put(dst, new_x, new_y, color);
            }
        }
    }
} */

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
				printf("x: %d- y: %d\n", y / REC_HEIGHT, x / REC_WIDTH);
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

int	main()
{
	t_cub3d	game;
	int		y;
	int		x;

	ft_memset(&game, 0, sizeof(t_cub3d));

	game.map.map = (int **)malloc(sizeof(int *) * (MAP_HEIGHT + 1));
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		game.map.map[y] = (int *)malloc(sizeof(int) * (MAP_WIDHT + 1));
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
	mlx_hook(game.win, 3, 0, key_up, &game);
	mlx_hook(game.win, 2, 0, key_down, &game);
	mlx_mouse_hook(game.win, mouse_click, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

