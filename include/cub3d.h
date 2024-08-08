#ifndef CUB3D_H
# define CUB3D_H

#ifdef __linux__

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_C		99
# define KEY_G		42

#elif __APPLE__ || __MACH__

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_C		8
# define KEY_G		5
#endif

# define	RAD_CONVERT		0.0174532925199432954743716805978692718781530857086181640625
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

#define BUFFER_SIZE	13

#include <stdbool.h>
#include <stdio.h>//////////////!!!!!!!!!!!!!!!!!!!!!!!!

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

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

typedef struct s_file
{
	char			**no;
	char			**so;
	char			**we;
	char			**ea;
	char			**map;
	unsigned int	f;
	unsigned int	c;
	int				map_height;
	int				map_width;
}	t_file;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}	t_map;

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

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	hex;
}	t_color;

typedef struct s_images
{
	t_image	N;
	t_image	E;
	t_image	S;
	t_image	W;
	t_image	background;
	t_color	floor_color;
	t_color	ceiling_color;
} t_images;

typedef struct s_ray
{
	t_vec2	pos;
	double	dis;
	double	angle;
	char	v_h;
}	t_ray;

typedef struct s_cub3d
{
	t_player	player;
	t_map		map;
	t_images	images;
	t_ray		rays[RAY_COUNT];
	void		*mlx;
	void		*win;
	bool		shadow;
	//t_player	player2; EĞLENCELİ
}	t_cub3d;

typedef struct s_tmp_map
{

} t_tmp_map;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-= END OF STRUCTS =-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

//*	create_map.c
void			draw_map(t_cub3d *game);
void			draw_rectangle(t_image img, int x, int y, int width,
							int height, bool grid, int color);
void			create_map(t_cub3d *game);

/* ------------------------------- LEVEL UTILS -------------------------------*/
// configure_level.c
void			configure_level(t_cub3d *game, char *file_name);

// file_reading.c
bool			extension_is_cub(char *file_name);
char			*read_file(int fd);

// seperate_content.c
t_file			separate_content(char *f_line);

unsigned int	get_colour(char *str);
char			*get_texture(char *str);
void			get_tmp_map(char *file_name);
void			print_map(char **map);
void			initialize_tmp_map(t_tmp_map *map);
void			free_tmp_map(t_tmp_map *map);
t_map			get_actual_map(t_tmp_map *tmp_map);
void			flood_fill(char **map, int y, int x);

// SHIT HITS THE FAN
size_t	str_arrlen(char **arr);

//*	key_hook.c
int		key_down(int keycode, t_cub3d *game);
int		key_up(int keycode, t_cub3d *game);
void	update_player_status(t_cub3d *game);
int		mouse_hook(int keycode, int x, int y, t_cub3d *game);

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

//*	color.c
t_color	rgb_to_color(int r, int g, int b);
t_color	hex_to_color(unsigned int hex);

//* cub3d_utils.c
void 		put_pixel_to_image(t_image img, int x, int y, unsigned int color);
t_color		blackout(t_color color, double ratio);
unsigned int	get_pixel_color(t_image img, int x, int y);

//!	dosyaya ayrılacak
t_ray	ray_throw(t_cub3d *game, double angle);

#endif
