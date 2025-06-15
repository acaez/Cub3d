#include "../../inc/cub3D.h"

static void	draw_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = game->config.ceiling_color ? game->config.ceiling_color : 0x87CEEB;
	floor_color = game->config.floor_color ? game->config.floor_color : 0x8B4513;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_game *game)
{
	draw_ceiling_floor(game);
	raycast(game);
	printf("map[0] = %s\n", game->map[0]);
	draw_minimap(game);
	if (game->debug_mode)
	{
		draw_map(game);
		draw_player_direction(game);
	}
}
