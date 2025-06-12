#include "../../inc/cub3D.h"

int	game_loop(t_game *game)
{
	move_player(&game->player);
	clear_image(game);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

