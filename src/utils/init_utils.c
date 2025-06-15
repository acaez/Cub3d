/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:07:32 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 16:11:28 by matsauva         ###   ########.fr       */
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
	cfg->ceiling_color = -1;
	cfg->map = NULL;
	cfg->map_width = -1;
	cfg->map_height = -1;
}

void	init_key(t_game *game)
{
#ifdef LINUX
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
#elif MACOS
	mlx_hook(game->win, 2, 0, key_press, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
#endif
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, "mlx_init() failed");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		exit_error(game, "mlx_new_window() failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		exit_error(game, "mlx_new_image() failed");
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		exit_error(game, "mlx_get_data_addr() failed");
}

void	init_player(t_player *player, t_game *game)
{
	player->x = -1;
	player->y = -1;
	player->angle = 0;
	player->speed = PLAYSPEED;
	player->rot_speed = ROTSPEED;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rot_left = false;
	player->rot_right = false;
	player->game = game;
	setup_pos(game);
	game->map = game->config.map;
}
