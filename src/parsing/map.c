/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 15:58:06 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_map(t_game *game, t_player *player)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	if (!map)
		return ;
	player->color = 0xFFFFFF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, player->color);
			x++;
		}
		y++;
	}
}

#define MINIMAP_MAX_CELLS 100 // !! global

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

	int	visible_w = px_max / cell_size;
	int	visible_h = py_max / cell_size;

	int	y = 0;
	while (y < visible_h)
	{
		int	x = 0;
		while (x < visible_w)
		{
			int	map_x = x;
			int	map_y = y;
			if (map_y < map_h && map_x < (int)ft_strlen(game->map[map_y])
				&& game->map[map_y][map_x] == '1')
			{
				draw_filled_square(game, x * cell_size, y * cell_size,
					cell_size, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}

	// Position du joueur (pas centré, juste placé à l'endroit correspondant)
	float	player_map_x = game->player.x / BLOCK;
	float	player_map_y = game->player.y / BLOCK;
	int	player_px = player_map_x * cell_size;
	int	player_py = player_map_y * cell_size;

	draw_filled_square(game, player_px - 2, player_py - 2, 4, 0xFF0000);
}