/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:05:58 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/10 17:06:01 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	main(int argc, char **argv)
{
	int			len;
	t_game		game;
	t_config 	config;
	size_t 		max_len;

	// Check arg
	if (argc != 2)
		return (printf("Usage: %s map.cub\n", argv[0]), 1);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (printf("Usage: %s map.cub\n", argv[0]), 1);

	// init memories
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&config, 0, sizeof(t_config));
	init_config(&config);

	// Parsing
	if (!parse_cub_file(&config, argv[1]))
		exit_with_error(&game, "Invalid .cub file");

	// Padding
	max_len = get_max_line_len(config.map);
	if (!pad_map_in_place(config.map, max_len, ' '))
		exit_with_error(&game, "Memory error while padding map");

	// Validate
	if (!validate_map(config.map))
		exit_with_error(&game, "Map is not valid");

	// init game
	config.map_width  = (int)max_len;
	config.map_height = get_map_height(config.map);
	game.config = &config;
	init_game(&game);
	init_player_from_map(&game);

	printf("[DEBUG] Initialization OK\n");

	// mlx hook
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, exit_game_hook, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);

	// Main game loop
	mlx_loop(game.mlx);

	// Exit
	if (game.img)
		mlx_destroy_image(game.mlx, game.img);
	if (game.win)
		mlx_destroy_window(game.mlx, game.win);
	if (game.mlx)
		mlx_destroy_display(game.mlx);
	if (game.mlx)
		free(game.mlx);
	free_map(game.map);
	free_config(&config);
	return (0);
}
