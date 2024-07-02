/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdemirbu <bdemirbu@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/02 17:45:24 by bdemirbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#include "../include/minilibx/mlx.h"
#include <stdio.h>

#define HEIGHT 100
#define WIDTH 100

static int	key_down(int keycode, t_cub3d *game)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 13 || keycode == 126)
		game->player.is_press_w = 1;
	if (keycode == 0 || keycode == 123)
		game->player.is_press_a = 1;
	if (keycode == 1 || keycode == 125)
		game->player.is_press_s = 1;
	if (keycode == 2 || keycode == 124)
		game->player.is_press_d = 1;
	return (0);
}

static int	key_up(int keycode, t_cub3d *game)
{
	if (keycode == 13 || keycode == 126)
		game->player.is_press_w = 0;
	if (keycode == 0 || keycode == 123)
		game->player.is_press_a = 0;
	if (keycode == 1 || keycode == 125)
		game->player.is_press_s = 0;
	if (keycode == 2 || keycode == 124)
		game->player.is_press_d = 0;
	return (0);
}

void	draw_rectangle(t_cub3d *game, t_vec2 vec, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < HEIGHT)
	{
		i_w = 0;
		while (i_w < WIDTH)
		{
			if (!(i_w == WIDTH - 1 || i_w == 0
				|| i_h == HEIGHT - 1 || i_h == 0))
				*(unsigned int*)(game->addr.canvas + (int)((vec.y + i_h) * game->addr.line_lenght+ (vec.x + i_w) * (game->addr.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
}

void	draw_map(t_cub3d *game)
{
	t_vec2	vec;
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			vec.x = x * WIDTH;
			vec.y = y * HEIGHT;
			if (game->map.map[y][x] == '1')
				color = 0x00781d1d;
			else
				color = 0x001d2078;
			draw_rectangle(game, vec, color);
			x++;
		}
		y++;
	}
}
#include <math.h>
int	game_loop(t_cub3d	*game)
{
	if (game->player.is_press_w)
		game->player.pos.y -= 1.5f;
	if (game->player.is_press_s)
	game->player.pos.y += 1.5f;
		if (game->player.is_press_d)
	game->player.pos.x += 1.5f;
		if (game->player.is_press_a)
	game->player.pos.x -= 1.5f;
	mlx_put_image_to_window(game->mlx, game->win, game->background, 0, 0);

	mlx_put_image_to_window(game->mlx, game->win, game->icon, game->player.pos.x, game->player.pos.y);
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
}

int	main()
{
	t_cub3d	game;

	ft_memset(&game, 0, sizeof(t_cub3d));
	game.map.map = (char **)malloc(sizeof(char *) * 11);
	game.map.map[0] = ft_strdup("1111111111");
	game.map.map[1] = ft_strdup("1000000001");
	game.map.map[2] = ft_strdup("1000000001");
	game.map.map[3] = ft_strdup("1000000001");
	game.map.map[4] = ft_strdup("1000000001");
	game.map.map[5] = ft_strdup("1000000001");
	game.map.map[6] = ft_strdup("1000000001");
	game.map.map[7] = ft_strdup("1000000001");
	game.map.map[8] = ft_strdup("1000000001");
	game.map.map[9] = ft_strdup("1111111111");
	game.map.map[10] = NULL;
	game.map.height = ft_strlen(*game.map.map);
	game.map.width = ft_strlen(game.map.map[0]);

	game.player.pos.x = game.map.width * WIDTH / 2;
	game.player.pos.y = game.map.height * HEIGHT / 2;

	game.mlx = mlx_init();
	if (!game.mlx)
		exit(0);
	game.win = mlx_new_window(game.mlx, game.map.height * HEIGHT, game.map.width * WIDTH, "naber müdür");
	if (!game.win)
		exit(0);
	game.background = mlx_new_image(game.mlx, game.map.height * HEIGHT, game.map.width * WIDTH);
	game.addr.canvas = mlx_get_data_addr(game.background, &game.addr.bits_per_pixel, &game.addr.line_lenght, &game.addr.endian);
	draw_map(&game);
	int i, y;
	game.icon = mlx_xpm_file_to_image(game.mlx, "./icon.xpm", &i, &y);
	mlx_hook(game.win, 3, 0, key_up, &game);
	mlx_hook(game.win, 2, 0, key_down, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

