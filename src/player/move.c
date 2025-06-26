/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:41:52 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:42:29 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	handle_rotation(t_player *player)
{
	if (player->rot_left)
		player->angle -= player->rot_speed;
	if (player->rot_right)
		player->angle += player->rot_speed;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
}

static void	try_move_player(t_player *player, float new_x, float new_y)
{
	t_game	*game;
	float	old_x;
	float	old_y;

	game = player->game;
	if (!game)
		return ;
	old_x = player->x;
	old_y = player->y;
	if (!check_collision(&game->config, new_x, old_y))
		player->x = new_x;
	if (!check_collision(&game->config, player->x, new_y))
		player->y = new_y;
	if (player->x == old_x && player->y == old_y
		&& !check_collision(&game->config, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	handle_movement_keys(t_player *player)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + cos(player->angle) * player->speed;
		new_y = player->y + sin(player->angle) * player->speed;
		try_move_player(player, new_x, new_y);
	}
	if (player->key_down)
	{
		new_x = player->x - cos(player->angle) * player->speed;
		new_y = player->y - sin(player->angle) * player->speed;
		try_move_player(player, new_x, new_y);
	}
}

static void	move_forward(t_player *player)
{
	float	new_x;
	float	new_y;

	if (!player || !player->game)
		return ;
	handle_movement_keys(player);
	if (player->key_left)
	{
		new_x = player->x + cos(player->angle - PI / 2)
			* player->speed * player->strafe;
		new_y = player->y + sin(player->angle - PI / 2)
			* player->speed * player->strafe;
		try_move_player(player, new_x, new_y);
	}
	if (player->key_right)
	{
		new_x = player->x + cos(player->angle + PI / 2)
			* player->speed * player->strafe;
		new_y = player->y + sin(player->angle + PI / 2)
			* player->speed * player->strafe;
		try_move_player(player, new_x, new_y);
	}
}

void	move_player(t_player *player)
{
	handle_rotation(player);
	move_forward(player);
}
