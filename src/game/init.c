/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:53:48 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:38:00 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_mlx(t_game *game)
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

static void	init_trigo(t_trigo *trigo)
{
	int		i;
	float	angle;

	trigo->table_size = 3600;
	trigo->cos_table = malloc(sizeof(float) * 3600);
	trigo->sin_table = malloc(sizeof(float) * 3600);
	if (!trigo->cos_table || !trigo->sin_table)
		return ;
	i = 0;
	while (i < 3600)
	{
		angle = (float)i * 2.0f * PI / (float)3600;
		trigo->cos_table[i] = cos(angle);
		trigo->sin_table[i] = sin(angle);
		i++;
	}
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
	if (game->debug_mode)
	{
		printf("Parsing OK\n");
		print_config(&game->config);
		print_map(game->config.map);
	}
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
		exit_error(NULL, "Usage: ./cub3D <map.cub> [--debug]");
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
		exit_error(NULL, "Usage: ./cub3D <map.cub> [--debug]");
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
	init_trigo(&game->trigo);
	game->last_frame = clock();
	init_player(&game->player, game);
	init_key(game);
}
