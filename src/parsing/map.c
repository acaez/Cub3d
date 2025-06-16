/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 12:22:29 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

#define MINIMAP_MAX_CELLS 100 // !! global

void	draw_filled_square(void *mlx, void *win, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx, win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	map_w = game->config.map_width;
	int	map_h = game->config.map_height;
	int	px_max = WIDTH * 2 / 10;
	int	py_max = HEIGHT * 2 / 10;
	int	cell_size_x = px_max / map_w;
	int	cell_size_y = py_max / map_h;
	int	cell_size = (cell_size_x < cell_size_y) ? cell_size_x : cell_size_y;

	if (cell_size < 1)
		cell_size = 1;

	// Nombre de cases visibles à l’écran
	int	visible_w = px_max / cell_size;
	int	visible_h = py_max / cell_size;

	// Position du joueur en cases
	int	player_map_x = game->player.x / BLOCK;
	int	player_map_y = game->player.y / BLOCK;

	// Coin haut gauche de la fenêtre visible
	int	start_x = player_map_x - visible_w / 2;
	int	start_y = player_map_y - visible_h / 2;

	// Affichage
	int	y = 0;
	while (y < visible_h)
	{
		int	x = 0;
		while (x < visible_w)
		{
			int	map_x = start_x + x;
			int	map_y = start_y + y;

			if (map_y >= 0 && map_y < map_h && map_x >= 0
				&& map_x < (int)ft_strlen(game->map[map_y])
				&& game->map[map_y][map_x] == '1')
			{
				draw_filled_square(game->mlx, game->win,
					x * cell_size, y * cell_size, cell_size, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}

	// Dessin du joueur (toujours centré dans la minimap)
	int	player_px = (visible_w / 2) * cell_size;
	int	player_py = (visible_h / 2) * cell_size;

	draw_filled_square(game->mlx, game->win, player_px - 2, player_py - 2, 4, 0xFF0000);
}
