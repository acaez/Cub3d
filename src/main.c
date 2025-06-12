#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game, ac, av);
	mlx_loop_hook(game.mlx, game_loop, &game);	// Not a "init responsabiliy, clearer to see the hook before mlx_loop"
	mlx_loop(game.mlx);
	return (0);
}
