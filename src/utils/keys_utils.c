/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:40:52 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 14:22:37 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

bool	handle_pause_keys(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		if (game->paused)
			close_window(game);
		else
		{
			game->paused = true;
			//mlx_mouse_show(game->mlx, game->win);
		}
		return (true);
	}
	if (keycode == SPACE && game->paused)
	{
		game->paused = false;
		//mlx_mouse_hide(game->mlx, game->win);
		//mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		return (true);
	}
	return (false);
}

bool	handle_debug_keys(int keycode, t_game *game)
{
	if (keycode == TAB)
	{
		game->debug_mode = !game->debug_mode;
		if (game->debug_mode)
			//mlx_mouse_show(game->mlx, game->win);
		//else
		{
			//mlx_mouse_hide(game->mlx, game->win);
			//mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		}
		return (true);
	}
	if (keycode == F)
	{
		game->show_fps = !game->show_fps;
		return (true);
	}
	return (false);
}

void	movement_keys(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = true;
	else if (keycode == S)
		game->player.key_down = true;
	else if (keycode == A)
		game->player.key_left = true;
	else if (keycode == D)
		game->player.key_right = true;
	else if (keycode == LEFT)
		game->player.rot_left = true;
	else if (keycode == RIGHT)
		game->player.rot_right = true;
}
