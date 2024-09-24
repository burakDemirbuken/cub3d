/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/24 10:30:43 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
 *	#define ERR_NOMAP	"cub3D: Invalid input\n"
 *	void	destroy_anim(void *mlx, t_frame *anim)
 *	void	configure_level(t_cub3d *game, char *file_name)
 *	void	initialize_rays(t_cub3d *game)
 *	int		key_up(int keycode, t_cub3d *game)
 *	int		key_down(int keycode, t_cub3d *game)
 *	int		mouse_hook(int keycode, int x, int y, t_cub3d *game)
 *	int		game_loop(t_cub3d *game)
 */
#include "libft/libft.h"
/*
 *	void	ft_strfree(char **a)
 *	void	ft_putstr_fd(char *s, int fd)
 *	#include <stdlib.h>
 *	-	void	exit(int)
 */
#include "minilibx/mlx.h"
/*
 *	int		mlx_destroy_image(void *mlx_ptr, void *img_ptr)
 *	void	*ft_memset(void *b, int c, size_t len)
 *	int		mlx_hook(void *win_ptr, int x_event, int x_mask,
 							int (*funct)(), void *param)
 *	int		mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param)
 *	int		mlx_loop(void *mlx_ptr)
 */
#include <unistd.h>
/*
 *	#define STDERR_FILENO	2
 */

void	end_program(t_cub3d *game, int e)
{
	if (game->map.map)
		ft_strfree(game->map.map);
	if (game->images.background.image)
		mlx_destroy_image(game->mlx, game->images.background.image);
	if (game->images.door.image)
		mlx_destroy_image(game->mlx, game->images.door.image);
	if (game->images.n.image)
		mlx_destroy_image(game->mlx, game->images.n.image);
	if (game->images.e.image)
		mlx_destroy_image(game->mlx, game->images.e.image);
	if (game->images.s.image)
		mlx_destroy_image(game->mlx, game->images.s.image);
	if (game->images.w.image)
		mlx_destroy_image(game->mlx, game->images.w.image);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(e);
}

int	exit_game(void *var)
{
	end_program((t_cub3d *)var, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	game;

	if (ac == 2)
	{
		ft_memset(&game, 0, sizeof(t_cub3d));
		configure_level(&game, av[1]);
		initialize_rays(&game);
		mlx_hook(game.win, 3, 1L << 0, key_up, &game);
		mlx_hook(game.win, 2, 1L << 1, key_down, &game);
		mlx_hook(game.win, 17, 0, exit_game, &game);
		mlx_loop_hook(game.mlx, game_loop, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	else
		return (ft_putstr_fd(ERR_NOMAP, STDERR_FILENO), 1);
}
