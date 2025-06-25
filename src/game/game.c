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

void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT * (game->bpp / 8))
	{
		game->data[i] = 0;
		i++;
	}
}
/*
static void	draw_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (game->config.floor_color != -1)
		color = game->config.floor_color;
	else
		color = 0x646464;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_sky(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (game->config.sky_color != -1)
		color = game->config.sky_color;
	else
		color = 0x87CEEB;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}
*/
void	draw_scene(t_game *game)
{
	if (!game)
		return ;
	if (game->debug_mode)
	{
		raycast(game);
	}
	else
	{
		//draw_floor(game);
		//draw_sky(game);
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
	return (0);
}
