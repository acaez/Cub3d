/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:50:08 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 14:40:21 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	exit_game(t_game *game, int exit_code)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
			mlx_destroy_display(game->mlx);
		if (game->mlx)
			free(game->mlx);
		free_config(&game->config);
		free_trigo(&game->trigo);
	}
	exit(exit_code);
}

void	exit_error(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		free(msg);
	}
	exit_game(game, 1);
}

int	close_window(t_game *game)
{
	mlx_mouse_show(game->mlx, game->win);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	exit_game(game, 0);
	return (0);
}
