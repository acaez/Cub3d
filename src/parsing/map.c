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

void	draw_filled_square(t_game *game, t_minimap minimap)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap.size)
	{
		j = 0;
		while (j < minimap.size)
		{
			put_pixel(game, minimap.x + i, minimap.y + j, minimap.color);
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
	if (cell_x < cell_y)
		m->cell_size = cell_x;
	else
		m->cell_size = cell_y;
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
			if (game->map[y][x] == '1')
				m->color = 0xAAAAAA;
			else
				m->color = 0x222222;
			m->x = m->origin_x + x * m->cell_size;
			m->y = m->origin_y + y * m->cell_size;
			m->size = m->cell_size;
			m->color = m->color;
			draw_filled_square(game, *m);
			x++;
		}
		y++;
	}
}

static void	draw_player_dot(t_game *game, t_minimap *m)
{
	int			px;
	int			py;
	t_minimap	square;

	px = m->origin_x + (int)(game->player.x * m->scale);
	py = m->origin_y + (int)(game->player.y * m->scale);
	square.x = px - 2;
	square.y = py - 2;
	square.size = 4;
	square.color = 0xFF0000;
	draw_filled_square(game, square);
}

void	draw_minimap(t_game *game)
{
	t_minimap	m;

	init_minimap(game, &m);
	draw_map_tiles(game, &m);
	draw_player_dot(game, &m);
}
