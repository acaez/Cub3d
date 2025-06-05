/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:25:36 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/05 15:38:49 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	exit_with_error(t_game *game, const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit_game(game, 1);  // Error exit
}

void	exit_game(t_game *game, int exit_code)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
#ifdef __linux__
		if (game->mlx)
			mlx_destroy_display(game->mlx);
#endif
		if (game->mlx)
			free(game->mlx);
		if (game->map)
			free_map(game->map);
	}
	exit(exit_code);
}

