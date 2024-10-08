/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:45:26 by bkorkut           #+#    #+#             */
/*   Updated: 2024/09/24 10:24:54 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= HEADERS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
// ☃

/* ------------------------------ KEYCODES ---------------------------------- */

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_G		5
# define KEY_H		4

/* ----------------------------- MATH DEFINES ------------------------------  */

# define MATH_2PI	6.28318530717958647692528676655900576	// 2 * PI
# define MATH_3PI_2	4.71238898038468985769396507491925432	// 3 * PI / 2
# define RAD_ANG	0.017453292519943295474371680597869271	// PI / 180

/* ----------------------------- ERROR MESSAGES ----------------------------- */

# define ERR_CUB3D	"cub3D"
# define ERR_NOMAP	"cub3D: Invalid input\n"
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
# define ERR_CRIMG "cub3D: Failed to create image\n"

/* ------------------------------ WALL HITS --------------------------------- */

# define NORTH		'N'
# define SOUTH		'S'
# define WEST		'W'
# define EAST		'E'
# define DOOR		'2'
# define WALL		'1'
# define EMPTY		'0'

/* -------------------------------- OTHER ----------------------------------- */
# define WINDOWS_WIDTH	1920
# define WINDOWS_HEIGHT	1080

// ekrandaki bir dikdörtgenin uzunluğu ve genişliği
# define REC_HEIGHT	100
# define REC_WIDTH	100

# define MOVE_SPEED	6

# define WALL_SIZE	150

# define PERSPECTIVE	60.0f
# define RAY_COUNT		1920

# include <stdbool.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= STRUCTS =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef struct s_int_vec2
{
	int	x;
	int	y;
}	t_int_vec2;

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
	long double	frame_second;
}	t_cub3d;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= SOURCE =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// main.c
void			end_program(t_cub3d *game, int e);

//*	key_mouse_hooks.c
int				key_down(int keycode, t_cub3d *game);
int				key_up(int keycode, t_cub3d *game);
int				mouse_hook(int keycode, int x, int y, t_cub3d *game);

/* ----------------------------- CONFIGURE LEVEL -----------------------------*/

// configure_level.c
void			configure_level(t_cub3d *game, char *file_name);
void			free_file(t_file *file);

// file_reading.c
bool			extension_is_cub(char *file_name);
char			*read_file(int fd);
bool			the_path_is_valid(char *path);

// initialize_mlx.c
bool			initialize_mlx(t_cub3d *game);

// seperate_content.c
t_file			separate_content(char *f_line);

// set_elements.c
bool			set_elements(char *content, t_file *file, int *flag);
bool			elements_valid(t_file *file, bool no_map, int count, int *flag);

// set_game_map.c
void			set_game_map(t_cub3d *game, t_file *file);

// set_game_player.c
void			set_game_player(t_cub3d *game);

// set_game_sprites.c
void			set_game_sprites(t_cub3d *game, t_file *file);
void			destroy_anim(void *mlx, t_frame *anim);

/* -------------------------------- GAME LOOP --------------------------------*/

// game_loop.c
int				game_loop(t_cub3d	*game);
long double		my_system_time(void);

// color_utils.c
t_color			rgb_to_color(int r, int g, int b);
t_color			hex_to_color(unsigned int hex);
t_color			blackout(t_color color, double ratio);

// minimap.c
void			mini_map(t_cub3d *game);

// paint_floor_ceiling.c
void			paint_floor_ceiling(t_cub3d *game);

// render_scene.c
void			render_scene(t_cub3d *game);

// render_utils.c
void			put_pixel_to_image(t_image img, int x, int y,
					unsigned int color);
unsigned int	get_pixel_color(t_image img, int x, int y);

// track_door.c
void			track_door(t_cub3d *game);

// update_player_status.c
void			update_player_status(t_cub3d *game);

/* ------------------------------- RAY CASTING ------------------------------ */

// initialize_rays.c
void			initialize_rays(t_cub3d *game);

//*	ray_caster.c
void			ray_caster(t_cub3d *game, t_ray *ray);

//*	ray_casting_utils.c
double			get_offset(t_vec2 p_pos, double rad, char v_h);
double			distance(t_vec2 point1, t_vec2 point2);
bool			inside_map(t_cub3d *game, t_vec2 ret);
void			ret_add(t_vec2 *ret, t_vec2 add, double rad);
char			hits_wall(t_cub3d *game, t_vec2 point, double rad, char v_h);

#endif
