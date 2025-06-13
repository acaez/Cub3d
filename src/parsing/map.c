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

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	if (!map)
		return ;
	color = 0xFFFFFF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	char	**map;
	int		x;
	int		y;
	int		px;
	int		py;

	map = game->map;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				draw_filled_square(game, x * BLOCK * MINIMAP_SCALE,
					y * BLOCK * MINIMAP_SCALE,
					BLOCK * MINIMAP_SCALE, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
	px = game->player.x * MINIMAP_SCALE;
	py = game->player.y * MINIMAP_SCALE;
	draw_filled_square(game, px - 2, py - 2, 4, 0xFF0000);
}
