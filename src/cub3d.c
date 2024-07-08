/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/07/08 21:55:11 by bkorkut          ###   ########.fr       */
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
#include <math.h>
#include <unistd.h>

// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
#define REC_HEIGHT	100
#define REC_WIDTH	100

// haritanın uzunluğu ve genişliği
#define MAP_HEIGHT	10
#define MAP_WIDHT	10

static int	key_down(int keycode, t_cub3d *game);
static int	key_up(int keycode, t_cub3d *game);
int	game_loop(t_cub3d	*game);
// tuşa basıldığı anda t_cub3d structda bulunun değerleri true yapıyor. Bu sayede tuşa basılı tuttuğunu anlaşılıyor.
static int	key_down(int keycode, t_cub3d *game)
{
	printf("Keycode: %d\n", keycode);
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
	{
		mlx_new_window(game->mlx, (MAP_WIDHT * REC_WIDTH) + 123, 124 + (MAP_HEIGHT * REC_HEIGHT), "asdasdasd müdür");

			mlx_hook(game->win, 3, 1L << 0, key_up, &game);
	mlx_hook(game->win, 2, 1L << 1, key_down, &game);
/* 	mlx_mouse_hook(game->win, mouse_click, &game); */

	}
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
void	draw_rectangle(t_cub3d *game, int x, int y, int width, int height, bool grid, int color)
{
	int		i_h;
	int		i_w;

	i_h = 0;
	while (i_h < height)
	{
		i_w = 0;
		while (i_w < width)
		{
			if (grid && !(i_w == width - 1 || i_w == 0
				|| i_h == height - 1 || i_h == 0))
				*(unsigned int*)(game->addr.canvas
				+ (int)((y + i_h) * game->addr.line_lenght
				+		(x + i_w) * (game->addr.bits_per_pixel / 8))) = 0;
			else
				*(unsigned int*)(game->addr.canvas
				+ (int)((y + i_h) * game->addr.line_lenght
				+		(x + i_w) * (game->addr.bits_per_pixel / 8))) = color;
			i_w++;
		}
		i_h++;
	}
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
			*(unsigned int*)(game->addr.canvas + (int)((y * game->addr.line_lenght) + (x * game->addr.bits_per_pixel / 8))) = color;
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
			*(unsigned int*)(game->addr.canvas + (int)(y * game->addr.line_lenght + x * (game->addr.bits_per_pixel / 8))) = color;
			y += sy;
			if (p > 0)
			{
				x += sx;
				p -= 2 * dy;
			}
			p += 2 * dx;
		}
	}

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
			if (game->map.map[y][x] == '1')
				draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, true, 0x00808080);
			else
				draw_rectangle(game, x * REC_WIDTH, y * REC_HEIGHT, REC_WIDTH, REC_HEIGHT, true, 0x00080808);
			x++;
		}
		y++;
	}
}

// Rotasyon fonksiyonu

t_vec2	rotate_around_point(t_vec2 point, t_vec2 pivot, double angle) {
	t_vec2	new_point;

	double rad = angle * (M_PI / 180.0);
	double temp_x = point.x - pivot.x;
	double temp_y = point.y - pivot.y;
	double rotated_x = temp_x * cos(rad) - temp_y * sin(rad);
	double rotated_y = temp_x * sin(rad) + temp_y * cos(rad);
	new_point.x = rotated_x + pivot.x;
	new_point.y = rotated_y + pivot.y;

	return new_point;
}

void	draw_player(t_cub3d *game)
{
	t_vec2 cor;

	draw_rectangle(game, game->player.pos.x - 10, game->player.pos.y - 10, 20, 20, false, 0x00FF0000);
	cor = rotate_around_point((t_vec2){game->player.pos.x + 100, game->player.pos.y}, game->player.pos, game->player.angle);
	bresenham_line(game, (int)game->player.pos.x, (int)game->player.pos.y, (int)cor.x, (int)cor.y, 0x0000FF00);

}
int	game_loop(t_cub3d	*game)
{
	int	x;
	int	y;

	// eğer tusa basılıysa değerleri artırır.
	if (game->player.is_press_w && game->player.pos.y > 0)
		game->player.pos.y -= 3.0f;
	if (game->player.is_press_s && game->player.pos.y < MAP_HEIGHT * REC_HEIGHT)
		game->player.pos.y += 3.0f;
	if (game->player.is_press_d && game->player.pos.x < MAP_WIDHT * REC_WIDTH)
		game->player.pos.x += 3.0f;
	if (game->player.is_press_a && game->player.pos.x > 0)
		game->player.pos.x -= 3.0f;
	if (game->player.is_press_p_totation)
	{
		game->player.angle += 3.0F;
		if (game->player.angle > 360)
			game->player.angle = 0;
	}
	if (game->player.is_press_n_totation)
	{
		game->player.angle -= 3.0F;
		if (game->player.angle < 0)
			game->player.angle = 360;
	}

	// mousenin olduğu kareyi farklı renge boyar.
/* 	#ifdef __linux__
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	#elif __APPLE__ || __MACH__
		mlx_mouse_get_pos(game->win, &x, &y);
	#endif
	if (!(x < 0 || y >= MAP_HEIGHT * REC_HEIGHT || y < 0 || x >= MAP_WIDHT * REC_WIDTH))
		draw_rectangle(game, (x / REC_WIDTH) * REC_WIDTH, (y / REC_HEIGHT) * REC_HEIGHT, REC_HEIGHT, REC_HEIGHT, true, 0x00808080); */
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->background, 0, 0);
	return (0);
}

// ilk tıklamada bir kare seçer ikinci tıklamada ise 1. tıklamayla 2. tıklama arasına çizgi çeker.
/* int	mouse_click(int keycode, int x, int y, t_cub3d *game)
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
} */

void	create_map(t_cub3d *game)
{
	int	x;
	int	y;

	game->map.map = (char **)malloc(sizeof(char *) * (MAP_HEIGHT + 1));
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		game->map.map[y] = (char *)malloc(sizeof(char) * (MAP_WIDHT + 1));
		while (x < MAP_WIDHT)
		{
			if ( x == 0 || y == 0  || x == MAP_WIDHT - 1 || y == MAP_HEIGHT -1)
				game->map.map[y][x] = '1';
			else
				game->map.map[y][x] = '0';
			x++;
		}
		game->map.map[y][x] = 0;
		y++;
	}
	game->map.map[y] = 0;
	game->map.map[4][6] = '1';
	game->map.map[2][3] = '1';
	game->map.map[5][6] = '1';
	game->map.map[5][7] = '1';
	game->map.map[3][7] = '1';
	game->map.map[1][3] = '1';
}

void	set_mlx(t_cub3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win = mlx_new_window(game->mlx, MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT, "naber müdür");
	if (!game->win)
		exit(0);
	game->background = mlx_new_image(game->mlx,  MAP_WIDHT * REC_WIDTH, MAP_HEIGHT * REC_HEIGHT);
	game->addr.canvas = mlx_get_data_addr(game->background, &game->addr.bits_per_pixel, &game->addr.line_lenght, &game->addr.endian);
	game->player.pos.x = MAP_WIDHT * REC_WIDTH / 2;
	game->player.pos.y = MAP_HEIGHT * REC_HEIGHT / 2;
	game->player.angle = (double)23;
}

// haritayı verilen genişliğe ve uzunluğa göre oluşturur
// pencere oluşturup oyunu başlatır.
int	main()
{
	t_cub3d	game;
	int		y;
	int		x;

	ft_memset(&game, 0, sizeof(t_cub3d));
	create_map(&game);
	set_mlx(&game);
	draw_map(&game);
	draw_player(&game);

	// int is, ys;
	// game.icon = mlx_xpm_file_to_image(game.mlx, "./icon.xpm", &is, &ys);
	mlx_hook(game.win, 3, 1L << 0, key_up, &game);
	mlx_hook(game.win, 2, 1L << 1, key_down, &game);
	// mlx_mouse_hook(game.win, mouse_click, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

