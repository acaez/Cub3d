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
	if (handle_pause_keys(keycode, game))
		return (0);
	if (handle_debug_keys(keycode, game))
		return (0);
	if (game->paused)
		return (0);
	movement_keys(keycode, game);
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

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	float	diff;
	float	sensitivity;

	(void)y;
	game = (t_game *)param;
	if (game->paused || game->debug_mode)
		return (0);
	diff = x - (WIDTH / 2);
	sensitivity = 0.002f;
	if (diff != 0)
	{
		game->player.angle += diff * sensitivity;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		else if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		mlx_mouse_move(game->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}
