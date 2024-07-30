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

# define	WINDOWS_WIDTH	1920
# define	WINDOWS_HEIGHT	1080

// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
# define	REC_HEIGHT	100
# define	REC_WIDTH	100

# define	MOVE_SPEED	6
// haritanın uzunluğu ve genişliği
# define	MAP_HEIGHT	20
# define	MAP_WIDTH	20

# define	WALL_SIZE	150

# define	PERSPECTIVE	60.0f
# define	RAY_COUNT	1920

#include <stdbool.h>
#include <stdio.h>//////////////!!!!!!!!!!!!!!!!!!!!!!!!

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec2	pos;
	double	dis;
	double	angle;
	char	v_h;
}	t_ray;

typedef struct s_image
{
	char	*data;
	void	*image;
	int		height;
	int		width;
	int		endian;
	int		line_lenght;
	int		bits_per_pixel;
}	t_image;

typedef struct s_images
{
	t_image	background;
} t_images;


typedef struct s_player
{
	t_vec2	pos;
	bool	is_press_w;
	bool	is_press_a;
	bool	is_press_s;
	bool	is_press_d;
	bool	is_press_n_rotation;
	bool	is_press_p_rotation;
	double	angle;
}	t_player;

typedef struct s_cub3d
{
	t_player	player;
	t_map		map;
	t_vec2		click;
	t_images	images;
	t_ray		rays[RAY_COUNT];
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
void	update_player_status(t_cub3d *game);

//* game_loop.c
int		game_loop(t_cub3d	*game);

//*	draw_player.c
void	draw_player(t_cub3d *game);
void	bresenham_line(t_image img, int x0, int y0, int x1, int y1, int color);

//*	ray_calculator.c
t_vec2	vertical_ray_calculator(t_cub3d *game, double rad, double tan_a);
t_vec2	horizontal_ray_calculator(t_cub3d *game, double rad, double tan_a);

//*	ray_calculator_utils.c
double	get_offset(t_vec2 p_pos, double rad, char v_h);
double	distance(t_vec2 point1,t_vec2  point2);

//*	display.c
void	display(t_cub3d *game);

#endif
