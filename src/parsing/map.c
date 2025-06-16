/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:00 by matsauva         ###   ########.fr       */
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

static void	init_minimap(t_game *game, t_minimap *m)
{
	int	px_max;
	int	py_max;
	int	cell_x;
	int	cell_y;

	px_max = WIDTH / 5;
	py_max = HEIGHT / 5;
	cell_x = px_max / game->config.map_width;
	cell_y = py_max / game->config.map_height;
	m->map_w = game->config.map_width;
	m->map_h = game->config.map_height;
	m->cell_size = (cell_x < cell_y) ? cell_x : cell_y;
	if (m->cell_size < 1)
		m->cell_size = 1;
	m->origin_x = 10;
	m->origin_y = 10;
	m->scale = (float)m->cell_size / (float)BLOCK;
}

static void	draw_map_tiles(t_game *game, t_minimap *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->map_h)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map[y]))
		{
			int	color = (game->map[y][x] == '1') ? 0xAAAAAA : 0x222222;
			draw_filled_square(game,
				m->origin_x + x * m->cell_size,
				m->origin_y + y * m->cell_size,
				m->cell_size, color);
			x++;
		}
		y++;
	}
}

static void	draw_player_dot(t_game *game, t_minimap *m)
{
	int	px;
	int	py;

	px = m->origin_x + (int)(game->player.x * m->scale);
	py = m->origin_y + (int)(game->player.y * m->scale);
	draw_filled_square(game, px - 2, py - 2, 4, 0xFF0000);
}

void	draw_minimap(t_game *game)
{
	t_minimap	m;

	init_minimap(game, &m);
	draw_map_tiles(game, &m);
	draw_player_dot(game, &m);
}

