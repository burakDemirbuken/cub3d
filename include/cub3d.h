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

#define	MOVE_SPEED	3
// haritanın uzunluğu ve genişliği
#define MAP_HEIGHT	11
#define MAP_WIDTH	11

#define WALL_HEIGHTf	500.0f

#define	PERSPECTIVE	60.0f
#define	RAY_COUNT	1100

#define BUFFER_SIZE	13

#include <stdbool.h>
#include <stdio.h>//////////////!!!!!!!!!!!!!!!!!!!!!!!!

typedef struct s_tmp_map
{
	char			**no;
	char			**so;
	char			**we;
	char			**ea;
	char			**map;
	unsigned int	f;
	unsigned int	c;
	int				height;
	int				width;
}	t_tmp_map;

typedef struct s_image
{
	char	*data;
	void	*image;
	int		endian;
	int		line_lenght;
	int		bits_per_pixel;
}	t_image;

typedef struct s_map
{
	t_image		no;
	t_image		so;
	t_image		we;
	t_image		ea;
	char		**map;
	unsigned int	f;
	unsigned int	c;
	int			height;
	int			width;
}	t_map;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec2	pos;
	float	dis;
	float	angle;
	char	v_h;
}	t_ray;

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
	t_vec2		horizontal_one_ray;
	t_vec2		vertical_one_ray;
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

// MAP UTILS
unsigned int	get_colour(char *str);
char			*get_texture(char *str);
void			get_tmp_map(char *file_name);
void			print_map(char **map);
char			*read_file(int fd);
void			is_cub(char *file_name);
t_tmp_map		separate_content(char *f_line);
void			initialize_tmp_map(t_tmp_map *map);
void			free_tmp_map(t_tmp_map *map);
t_map			get_actual_map(t_tmp_map *tmp_map);
void			flood_fill(char **map, int y, int x);

//*	key_hook.c
int		key_down(int keycode, t_cub3d *game);
int		key_up(int keycode, t_cub3d *game);

//* game_loop.c
int		game_loop(t_cub3d	*game);

//*	draw_player.c
void	draw_player(t_cub3d *game);
void	bresenham_line(t_image img, int x0, int y0, int x1, int y1, int color);

//*	ray_calculator.c
t_vec2	vertical_ray_calculator(t_cub3d *game, float rad, float tan_a);
t_vec2	horizontal_ray_calculator(t_cub3d *game, float rad, float tan_a);

//*	ray_calculator_utils.c
float	get_offset(t_vec2 p_pos, float rad, char v_h);
float	distance(t_vec2 point1,t_vec2  point2);

// utilities
void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size);

#endif
