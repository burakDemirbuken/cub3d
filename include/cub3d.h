#ifndef CUB3D_H
# define CUB3D_H


#ifdef __linux__

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_C 99

#elif __APPLE__ || __MACH__

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_C 8

#endif
// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
#define REC_HEIGHT	100
#define REC_WIDTH	100

#define REC_HEIGHTf	100.0f
#define REC_WIDTHf	100.0f
// haritanın uzunluğu ve genişliği
#define MAP_HEIGHT	11
#define MAP_WIDHT	11

#include <stdbool.h>

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}	t_map;


typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_image
{
	char	*data;
	void	*image;
	int		endian;
	int		line_lenght;
	int		bits_per_pixel;
}	t_image;

typedef struct s_images
{
	t_image	background;
	t_image	floor;
	t_image	wall;
} t_images;


typedef struct s_player
{
	t_vec2	pos;
	bool	is_press_w;
	bool	is_press_a;
	bool	is_press_s;
	bool	is_press_d;
	bool	is_press_n_totation;
	bool	is_press_p_totation;
	double	angle;
}	t_player;

typedef struct s_cub3d
{
	t_player	player;
	t_map		map;
	t_vec2		click;
	t_images	images;
	t_vec2		y_one_ray;
	bool		is_click;
	void		*mlx;
	void		*win;
	//t_player	player2; EĞLENCELİ
}	t_cub3d;

//*	create_map.c
void	draw_map(t_cub3d *game);
void	draw_rectangle(t_image img, int x, int y, int width,
							int height, bool grid, int color);
void	create_map(t_cub3d *game);

//*	key_hook.c
int		key_down(int keycode, t_cub3d *game);
int		key_up(int keycode, t_cub3d *game);

//* game_loop.c
int		game_loop(t_cub3d	*game);

//*	draw_player.c
void	draw_player(t_cub3d *game);
void	bresenham_line(t_image img, int x0, int y0, int x1, int y1, int color);

//*	ray_calculator.c
t_y_ray	y_ray_calculator(t_cub3d *game);
#endif
