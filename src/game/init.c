/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:53:48 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 16:11:04 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, ft_strdup("mlx_init() failed"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		exit_error(game, ft_strdup("mlx_new_window() failed"));
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		exit_error(game, ft_strdup("mlx_new_image() failed"));
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!game->data)
		exit_error(game, ft_strdup("mlx_get_data_addr() failed"));
}

static void	load_game(t_game *game, char *map_path, int debug_mode)
{
	char	*err;

	err = NULL;
	ft_memset(game, 0, sizeof(t_game));
	game->debug_mode = debug_mode;
	init_config(&game->config);
	if (!parse_cub_file(&game->config, map_path, &err))
		exit_error(game, err);
	if (!validate_config(&game->config, &err))
		exit_error(game, err);
	if (game->debug_mode)
		printf("Config OK\n");
	if (!validate_map(game->config.map, &err))
		exit_error(game, err);
	if (game->debug_mode)
		printf("Map OK\n");
}

static void	parse_args(int argc, char **argv, int *map_idx, int *debug)
{
	if (argc < 2 || argc > 3)
		exit_error(NULL, ft_strdup("Usage: ./cub3D <map.cub> [--debug]"));
	*debug = 0;
	*map_idx = -1;
	if (argc == 2)
	{
		*map_idx = 1;
		return ;
	}
	if (ft_strcmp(argv[1], "--debug") == 0)
	{
		*debug = 1;
		*map_idx = 2;
	}
	else if (ft_strcmp(argv[2], "--debug") == 0)
	{
		*debug = 1;
		*map_idx = 1;
	}
	else
		exit_error(NULL, ft_strdup("Usage: ./cub3D <map.cub> [--debug]"));
}

static void	init_player(t_player *player, t_game *game)
{
	player->x = -1;
	player->y = -1;
	player->angle = 0;
	player->speed = 0.021 * BLOCK;
	player->rot_speed = 0.02;
	player->strafe = 0.5;
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

void	init_game(t_game *game, int argc, char **argv)
{
	int	map_arg;
	int	debug;

	map_arg = -1;
	debug = 0;
	parse_args(argc, argv, &map_arg, &debug);
	load_game(game, argv[map_arg], debug);
	init_minimap(game);
	init_mlx(game);
	init_player(&game->player, game);
	init_key(game);
	init_fps(game);
}
