/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 17:46:55 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_filled_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	print_minimap_debug(int map_w, int map_h, int cell_size, int ox, int oy)
{
	printf("[MINIMAP DEBUG]\n");
	printf("Map size       : width = %d, height = %d\n", map_w, map_h);
	printf("Cell size      : %d pixels\n", cell_size);
	printf("Minimap origin : (%d, %d)\n", ox, oy);
	printf("Minimap frame  :\n");
	printf("  Top-Left     : (%d, %d)\n", ox, oy);
	printf("  Top-Right    : (%d, %d)\n", ox + map_w * cell_size, oy);
	printf("  Bottom-Left  : (%d, %d)\n", ox, oy + map_h * cell_size);
	printf("  Bottom-Right : (%d, %d)\n", ox + map_w * cell_size, oy + map_h * cell_size);
}

void	draw_minimap(t_game *game) // Debuging in progress
{
	int	map_w = game->config.map_width;
	int	map_h = game->config.map_height;
	int	px_max = WIDTH / 5;
	int	py_max = HEIGHT / 5;
	int	cell_size_x = px_max / map_w;
	int	cell_size_y = py_max / map_h;
	int	cell_size;
	int	x, y;
	int	origin_x = 10;
	int	origin_y = 10;

	cell_size = (cell_size_x < cell_size_y) ? cell_size_x : cell_size_y;
	if (cell_size < 1)
		cell_size = 1;
	y = 0;
	while (y < map_h)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			int color = 0x222222;
			if (game->map[y][x] == '1')
				color = 0xAAAAAA;

			draw_filled_square(game,
				origin_x + x * cell_size,
				origin_y + y * cell_size,
				cell_size, color);
			x++;
		}
		y++;
	}
	print_minimap_debug(map_w, map_h, cell_size, origin_x, origin_y);
	float scale = (float)cell_size / (float)BLOCK;
	int px = origin_x + (int)(game->player.x * scale);
	int py = origin_y + (int)(game->player.y * scale);
	printf("[MINIMAP] Player in world: (%.2f, %.2f)\n", game->player.x, game->player.y);
	printf("[MINIMAP] Player in minimap: (%d, %d)\n", px, py);
	float map_px_width = map_w * BLOCK;
	float map_px_height = map_h * BLOCK;
	if (game->player.x < 0 || game->player.x > map_px_width ||
		game->player.y < 0 || game->player.y > map_px_height)
	{
		printf("[MINIMAP] Player out of map bounds — not drawn\n");
		return;
	}
	draw_filled_square(game, (int)(px - 2), (int)(py - 2), 4, 0xFF0000);
}
