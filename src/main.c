#include "../inc/cub3D.h"

int	main(void)
{
	t_game	game;
	
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}
