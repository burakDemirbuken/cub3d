/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/09/21 15:26:27 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#ifdef __linux__
# include "../includes/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../includes/minilibx/mlx.h"
#endif
#include <stdlib.h>
#include <unistd.h>
// STDERR_FILENO

// Assumes all error messages were printed before calling this function.
// Frees all allocated memory and exits the program.
void	end_program(t_cub3d *game, int e)
{
	if (game->map.map)
		free(game->map.map);
	if (game->images.background.image)
		mlx_destroy_image(game->mlx, game->images.background.image);
	if (game->images.door.image)
		mlx_destroy_image(game->mlx, game->images.door.image);
	if (game->images.minimap.image)
		mlx_destroy_image(game->mlx, game->images.minimap.image);
	if (game->images.n)
		destroy_anim(game->mlx, game->images.n);
	if (game->images.e)
		destroy_anim(game->mlx, game->images.e);
	if (game->images.s)
		destroy_anim(game->mlx, game->images.s);
	if (game->images.w)
		destroy_anim(game->mlx, game->images.w);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(e);
}

int	exit_game(void *var)
{
	end_program((t_cub3d *)var, 0);
	return (0);
}

//! çarpıya basıldığında düzgün bir şekilde kapatılması.
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
		mlx_hook(game.win, 4, 1L << 2, mouse_hook, &game);
		mlx_hook(game.win, 17, 0, exit_game, &game);
		mlx_loop_hook(game.mlx, game_loop, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	else
		return (ft_putstr_fd(ERR_NOMAP, STDERR_FILENO), 1);
}
