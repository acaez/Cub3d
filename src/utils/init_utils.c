/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:07:32 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 16:30:39 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	init_config(t_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->floor_color = -1;
	cfg->sky_color = -1;
	cfg->map = NULL;
	cfg->map_width = -1;
	cfg->map_height = -1;
}

void	init_key(t_game *game)
{
	mlx_hook(game->win, 2, KEY_PRESS_MASK, key_press, game);
	mlx_hook(game->win, 3, KEY_RELEASE_MASK, key_release, game);
	mlx_hook(game->win, 17, DESTROY_MASK, close_window, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(game->win, 6, (1L << 6), mouse_move, game);
}

void	setup_dir(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player.angle = PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = PI;
}

void	setup_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->config.map[y])
	{
		x = 0;
		while (game->config.map[y][x])
		{
			if (ft_strchr("NSEW", game->config.map[y][x]))
			{
				game->player.x = x * BLOCK + BLOCK / 2;
				game->player.y = y * BLOCK + BLOCK / 2;
				setup_dir(game, game->config.map[y][x]);
				game->config.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_game *game)
{
	player->x = -1;
	player->y = -1;
	player->angle = 0;
	player->speed = 0.04 * BLOCK;
	player->rot_speed = 0.04;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rot_left = false;
	player->rot_right = false;
	player->game = game;
	player->config = game->config;
	game->map = game->config.map;
	game->paused = false;
	setup_pos(game);
}
