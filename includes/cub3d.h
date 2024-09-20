/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:45:26 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/20 15:52:52 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= HEADERS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#ifndef CUB3D_H
# define CUB3D_H
// ☃

/* ------------------------------ KEYCODES ---------------------------------- */
# ifdef __linux__

#  define KEY_W		119
#  define KEY_A		97
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_ESC	65307
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_C		99
#  define KEY_G		42
#  define KEY_H		43
// define M for mouse
// define N for hide mouse
// define Q for object interaction

# elif __APPLE__ || __MACH__

#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_ESC	53
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
#  define KEY_C		8
#  define KEY_G		5
#  define KEY_H		4
#  define KEY_M		46
#  define KEY_N		45
#  define KEY_Q		12
# endif

/* ----------------------------- MATH DEFINES ------------------------------  */

# define MATH_2PI	6.28318530717958647692528676655900576	// 2 * PI
# define MATH_3PI_2	4.71238898038468985769396507491925432	// 3 * PI / 2
# define RAD_ANG	0.017453292519943295474371680597869271	// PI / 180

/* ----------------------------- ERROR MESSAGES ----------------------------- */

# define ERR_CUB3D	"cub3D"
# define ERR_NOMAP	"cub3D: There is no map\n"
# define ERR_MUNDEF	"cub3D: Map has undefined elements\n"
# define ERR_NOWALL	"cub3D: Map must be surrounded by walls\n"
# define ERR_MSMALL	"cub3D: Map is too small\n"
# define ERR_ELMNUM	"cub3D: Wrong number of elements\n"
# define ERR_ELMISS	"cub3D: Missing elements\n"
# define ERR_COLNUM	"cub3D: Wrong number of colors\n"
# define ERR_COLINV	"cub3D: Invalid colors\n"
# define ERR_PUNDEF	"cub3D: Player starting position is undefined\n"
# define ERR_FEXT	"cub3D: File extension must be .cub\n"
# define ERR_FEMT	"cub3D: File is empty\n"

/* ------------------------------ WALL HITS --------------------------------- */

#define NORTH		'N'
#define SOUTH		'S'
#define WEST		'W'
#define EAST		'E'
#define DOOR		'2'

/* -------------------------------- OTHER ----------------------------------- */
# define WINDOWS_WIDTH	1920
# define WINDOWS_HEIGHT	1080

// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
# define REC_HEIGHT	100
# define REC_WIDTH	100

# define MOVE_SPEED	6

// haritanın uzunluğu ve genişliği
# define MAP_HEIGHT	20
# define MAP_WIDTH	20

# define WALL_SIZE	150

# define PERSPECTIVE	60.0f
# define RAY_COUNT		1920

# define BUFFER_SIZE	13

# include <stdbool.h>
# include <stdio.h>//////////////!!!!!!!!!!!!!!!!!!!!!!!!

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= STRUCTS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	hex;
}	t_color;

typedef struct s_file
{
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	char	**map;
	t_color	f;
	t_color	c;
	int		map_height;
	int		map_width;
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

typedef struct s_frame
{
	t_image			texture;
	int				frame_speed;
	struct s_frame	*next;
	struct s_frame	*prev;
}	t_frame;

typedef struct s_images
{
	t_frame	*n;
	t_frame	*e;
	t_frame	*s;
	t_frame	*w;
	t_image	door;
	t_image	background;
	t_image	minimap;
}	t_images;

typedef struct s_ray
{
	t_vec2	pos;
	double	dis;
	double	persp_angle;
	double	relat_angle;
	char	v_h;
	char	hit;
}	t_ray;

/* ------------------------------ GAME STRUCT ------------------------------- */
typedef struct s_cub3d
{
	t_player	player;
	t_map		map;
	t_images	images;
	t_ray		rays[RAY_COUNT];
	t_color		floor;
	t_color		ceiling;
	void		*mlx;
	void		*win;
	bool		shadow;
	bool		mouse_control;
	int			track_door[2];
	long double	door_time;
	long double	second;
}	t_cub3d;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= FUNCTIONS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

// cub3d.c
void			end_program(t_cub3d *game, int e);

/* ------------------------------ LEVEL UTILS --------------------------------*/
// configure_level.c
void			configure_level(t_cub3d *game, char *file_name);
void			free_file(t_file *file);

// file_reading.c
bool			extension_is_cub(char *file_name);
bool			the_path_is_valid(char *file_name);
char			*read_file(int fd);

// initialize_mlx.c
bool			initialize_mlx(t_cub3d *game);

// seperate_content.c
t_file			separate_content(char *f_line);

// set_elements.c
int				set_elements(char *content, t_file *file, int *flag);
int				elements_valid(t_file *file, int i, int map_start,
					int count, int *flag);

// set_game_map.c
void			set_game_map(t_cub3d *game, t_file *file);

// set_game_player.c
void			set_game_player(t_cub3d *game);

// set_game_sprites.c
void			set_game_sprites(t_cub3d *game, t_file *file);
void			destroy_anim(void *mlx, t_frame *anim);

// delete this
void			print_map(char **map);

// -----------------------------------------------------------------------------
// paint_floor_ceiling.c
void			paint_floor_ceiling(t_cub3d *game);

// initialize_rays.c
void			initialize_rays(t_cub3d *game);

/* ------------------------------ OTHER FILES ------------------------------- */
//*	key_hook.c
int				key_down(int keycode, t_cub3d *game);
int				key_up(int keycode, t_cub3d *game);
int				mouse_hook(int keycode, int x, int y, t_cub3d *game);

//* game_loop.c
int				game_loop(t_cub3d	*game);

//*	ray_casting_utils.c
double			get_offset(t_vec2 p_pos, double rad, char v_h);
double			distance(t_vec2 point1, t_vec2 point2);
bool			inside_map(t_cub3d *game, t_vec2 ret);
void			ret_add(t_vec2 *ret, t_vec2 add, double rad);
char			hits_wall(t_cub3d *game, t_vec2 point, double rad, char v_h);

//*	ray_caster.c
void			ray_caster(t_cub3d *game, t_ray *ray);

//*	display.c
void			render_scene(t_cub3d *game);

//*	color.c
t_color			rgb_to_color(int r, int g, int b);
t_color			hex_to_color(unsigned int hex);
t_color			blackout(t_color color, double ratio);

//* cub3d_utils.c
void			put_pixel_to_image(t_image img, int x, int y,
					unsigned int color);
unsigned int	get_pixel_color(t_image img, int x, int y);

//*	update_player_status.c
void			update_player_status(t_cub3d *game);


void	mini_map(t_cub3d *game);

void	track_door(t_cub3d *game);
long double       my_system_time(void);

#endif
