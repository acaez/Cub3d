/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:26:48 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_filled_square(t_game *game, t_square sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			put_pixel(game, sq.x + i, sq.y + j, sq.color);
			j++;
		}
		i++;
	}
}

void	init_minimap(t_game *game, t_minimap *m)
{
	int	px_max;
	int	py_max;
	int	cell_x;
	int	cell_y;

	px_max = WIDTH / 5;
	py_max = HEIGHT / 5;
	cell_x = px_max / ZONE_WIDTH;
	cell_y = py_max / ZONE_HEIGHT;
	if (cell_x < cell_y)
		m->cell_size = cell_x;
	else
		m->cell_size = cell_y;
	if (m->cell_size < 1)
		m->cell_size = 1;
	m->map_w = game->config.map_width;
	m->map_h = game->config.map_height;
	m->origin_x = 10;
	m->origin_y = 10;
	m->scale = (float)m->cell_size / (float)BLOCK;
}
