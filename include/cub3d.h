#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>

typedef struct s_map
{
	char	**map;
	int		height;
	int		widht;
}	t_map;


typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_player
{
	t_vec2	pos;
	bool	is_press_w;
	bool	is_press_a;
	bool	is_press_s;
	bool	is_press_d;
}	t_player;


typedef struct s_cub3d
{
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*win;
	//t_player	player2; EĞLENCELİ
}	t_cub3d;


#endif
