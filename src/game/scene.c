#include "../../inc/cub3D.h"

static void	draw_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (game->config.floor_color)
		color = game->config.floor_color;
	else
		color = 0x87CEEB;
	y = HEIGHT / 2;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_sky(t_game *game)
{
	int	x;
	int	y;
	int	color;

	if (game->config.sky_color)
		color = game->config.sky_color;
	else
		color = 0x87CEEB;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_game *game)
{
	draw_floor(game);
	draw_sky(game);
	raycast(game);
	//printf("map[0] = %s\n", game->map[0]);
	draw_minimap(game);
}
