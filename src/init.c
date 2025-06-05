#include "../inc/cub3D.h"

void	init_key(t_game *game)
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

void	init_player(t_player *player, t_game *game)
{
	player->x = 
	player->y = 
	player->angle = PI / 2;
	player->speed = 3.0;
	player->rot_speed = 0.05;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rot_left = false;
	player->rot_right = false;
	player->game = game;
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, "Error: mlx_init() failed");
	game->map = get_map();
	if (!game->map)
		exit_error(game, "Error: Failed to load the map");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		exit_error(game, "Error: mlx_new_window() failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		exit_error(game, "Error: mlx_new_image() failed");
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
		exit_error(game, "Error: mlx_get_data_addr() failed");
	game->debug_mode = DEBUG; // Initialize debug mode from the DEBUG macro
	init_key(game);
	init_player(&game->player, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

