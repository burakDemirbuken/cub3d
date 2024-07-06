#ifndef CUB3D_H
# define CUB3D_H

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
