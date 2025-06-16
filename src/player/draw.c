#include "../../inc/cub3D.h"

void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT * (game->bpp / 8))
	{
		game->data[i] = 0;
		i++;
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		index = y * game->size_line + x * (game->bpp / 8);
		game->data[index] = color & 0xFF;
		game->data[index + 1] = (color >> 8) & 0xFF;
		game->data[index + 2] = (color >> 16) & 0xFF;
	}
}

static void horizontal_line(t_game *game, int x, int y, int size)
{

}

static void	vertical_line(t_game *game, int x, int y, int size)
{

}

void	draw_square(t_game *game, int x, int y, int size)
{
	horizontal_line();
	horizontal_line();
	vertical_line();
	vertical_line();
}


