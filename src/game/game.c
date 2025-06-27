/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:44:21 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:21:44 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->window_width * game->window_height * (game->bpp / 8))
	{
		game->data[i] = 0;
		i++;
	}
}

static void	draw_scene(t_game *game)
{
	if (!game)
		return ;
	if (game->debug_mode)
		debug_mode(game);
	else
	{
		raycast(game);
		draw_crosshair(game);
		if (game->config.map)
			draw_minimap(game);
	}
}

int	game_loop(t_game *game)
{
	if (!game->paused)
		move_player(&game->player);
	clear_image(game);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->paused)
		draw_pause_overlay(game);
	update_fps(game);
	draw_fps(game);
	return (0);
}
