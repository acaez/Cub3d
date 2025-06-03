#include "../inc/cub3D.h"

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

void	draw_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		put_pixel(game, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(game, x + i, y + size, color);
		i++;
	}
	j = 0;
	while (j < size)
	{
		put_pixel(game, x, y + j, color);
		j++;
	}
	j = 0;
	while (j < size)
	{
		put_pixel(game, x + size, y + j, color);
		j++;
	}
}

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
