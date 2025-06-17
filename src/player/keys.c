/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:40:52 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:40:59 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		close_window(game);
		return (0);
	}
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
	else if (keycode == TAB)
		game->debug_mode = !game->debug_mode;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = false;
	else if (keycode == S)
		game->player.key_down = false;
	else if (keycode == A)
		game->player.key_left = false;
	else if (keycode == D)
		game->player.key_right = false;
	else if (keycode == LEFT)
		game->player.rot_left = false;
	else if (keycode == RIGHT)
		game->player.rot_right = false;
	return (0);
}
