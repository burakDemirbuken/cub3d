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

#include <stdbool.h>

typedef struct s_map
{
	unsigned int		**map;
	int					height;
	int					width;
}	t_map;


typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_addr
{
	char	*canvas;
	int		endian;
	int		bits_per_pixel;
	int		line_lenght;
}	t_addr;

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
	t_addr		addr;
	t_vec2		click;
	bool		is_click;
	void		*icon;
	void		*background;
	void		*mlx;
	void		*win;
	//t_player	player2; EĞLENCELİ
}	t_cub3d;


#endif
