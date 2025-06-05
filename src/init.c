#include "../inc/cub3D.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		exit_game(game, "Error: mlx_init() failed");
	game->map = get_map();
	if (game->map == NULL)
		exit_game(game, "Error: Failed to load the map");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		exit_game(game, "Error: mlx_new_window() failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img == NULL)
		exit_game(game, "Error: mlx_new_image() failed");
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (game->data == NULL)
		exit_game(game, "Error: mlx_get_data_addr() failed");
}

void	init_player(t_player *player, t_game *game)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->speed = 5.0;
	player->rot_speed = 0.05;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rot_left = false;
	player->rot_right = false;
	player->game = game;
}

void	exit_game(t_game *game, char *error_msg)
{
	if (error_msg)
		ft_putendl_fd(error_msg, 2);
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
#ifdef __linux__
		if (game->mlx)
			mlx_destroy_display(game->mlx);
#endif
		if (game->mlx)
			free(game->mlx);
		if (game->map)
			free_map(game->map);
	}
	if (error_msg)
		exit(1);
	else
		exit(0);
}
