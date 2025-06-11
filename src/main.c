#include "../inc/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (argc != 2)
	{
		printf("Error: Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	
	ft_memset(&game, 0, sizeof(t_game));
	
	// Initialize the config
	init_config(&game.config);
	
	// Parse the map file
	if (!parse_cub_file(&game.config, argv[1]))
	{
		printf("Error: Failed to parse map file\n");
		return (1);
	}
	
	// Validate the map
	if (!validate_map(game.config.map))
	{
		printf("Error: Invalid map\n");
		return (1);
	}
	
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}
