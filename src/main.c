#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game, ac, av);
	mlx_loop(game.mlx);
	return (0);
}
