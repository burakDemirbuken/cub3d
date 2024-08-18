/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:24:48 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/18 16:16:45 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libft/libft.h"
#ifdef __linux__
# include "../include/minilibx_linux/mlx.h"
#elif __APPLE__ || __MACH__
# include "../include/minilibx/mlx.h"
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
	if (game->images.N)
		destroy_anim(game->mlx, game->images.N);
	if (game->images.E)
		destroy_anim(game->mlx, game->images.E);
	if (game->images.S)
		destroy_anim(game->mlx, game->images.S);
	if (game->images.W)
		destroy_anim(game->mlx, game->images.W);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	exit (e);
}

int	main(int ac, char **av)
{
	t_cub3d	game;

	if (ac == 2)
	{
		ft_memset(&game, 0, sizeof(t_cub3d));
		configure_level(&game, av[1]);
		// draw_map(&game);
		// draw_player(&game);
		mlx_hook(game.win, 3, 1L << 0, key_up, &game);
		mlx_hook(game.win, 2, 1L << 1, key_down, &game);

		// mlx_mouse_hook(game.win, mouse_click, &game);
		mlx_loop_hook(game.mlx, game_loop, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	else
		return (ft_putstr_fd(ERR_NOMAP, STDERR_FILENO), 1);
}
