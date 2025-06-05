#include "../inc/cub3D.h"

int	main(int argc, char **argv)
{
	int			len;
	t_game		game;
	t_config 	config;
	
	len = ft_strlen(argv[1]);
	if (argc != 2 || len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		return (printf("Usage: %s map.cub\n", argv[0]), 1);
	ft_memset(&game, 0, sizeof(t_game));
	if (!parse_cub_file(&config, argv[1]))
		exit_with_error(&game, "Invalid .cub file");
	game.config = config;
	init_game(&game);
	init_player(&game.player, &game);
	mlx_hook(game.win, 2, 0, (void *)key_press, &game.player);
	mlx_hook(game.win, 3, 0, (void *)key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	if (game.img)
		mlx_destroy_image(game.mlx, game.img);
	if (game.win)
		mlx_destroy_window(game.mlx, game.win);
	if (game.mlx)
		mlx_destroy_display(game.mlx);
	if (game.mlx)
		free(game.mlx);
	if (game.map)
		free_map(game.map);
	return (0);
}
