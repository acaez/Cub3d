#include "../../inc/cub3D.h"

void	print_config_debug(t_config *cfg)
{
	printf("Config debug dump:\n");
	printf("NO: %s\n", cfg->no_path);
	printf("SO: %s\n", cfg->so_path);
	printf("WE: %s\n", cfg->we_path);
	printf("EA: %s\n", cfg->ea_path);
	printf("Floor:   %06X\n", cfg->floor_color);
	printf("Ceiling: %06X\n", cfg->ceiling_color);
	printf("Map size: %d x %d\n", cfg->map_width, cfg->map_height);
	printf("Map:\n");
	if (!cfg->map)
	{
		printf("(null)\n");
		return ;
	}
	int	y = 0;
	while (cfg->map[y])
	{
		int	x = 0;
		while (cfg->map[y][x])
		{
			if (cfg->map[y][x] == ' ')
				printf("*"); // to see spaces
			else
				printf("%c", cfg->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

// If a function is only used in one .c file, make it static.
// This avoids declaring it in the .h file and keeps it private.

void	init_key(t_game *game)		// Should be static
{
#ifdef LINUX
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);
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
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		exit_error(game, "mlx_get_data_addr() failed");
	game->debug_mode = DEBUG;
}

void	init_player(t_player *player, t_game *game)
{
	player->x = -1;			// will be define in setup_pos
	player->y = -1;			// will be define in setup_pos
	player->angle = 0;		// will be define in setup_pos
	player->speed = 3.0;
	player->rot_speed = 0.05;
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

void	init_game(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		exit_error(NULL, "Usage: ./cub3D <map.cub>");
	ft_memset(game, 0, sizeof(t_game));
	init_config(&game->config);
	if (!parse_cub_file(&game->config, argv[1]))
		exit_error(game, "Failed to parse map file");
	printf("Parsing OK\n");
	print_config_debug(&game->config);
	if (!validate_config(&game->config))
		exit_error(game, "Invalid configuration");
	printf("Config OK\n");
	if (!validate_map(game->config.map))
		exit_error(game, "Invalid map");
	printf("Map OK\n");
	init_mlx(game);
	init_player(&game->player, game);
	init_key(game);
}
