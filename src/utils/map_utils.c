/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 15:15:44 by matsauva         ###   ########.fr       */
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

static int	calculate_cell_size(t_config *cfg, int px_max, int py_max)
{
	int	cell_x;
	int	cell_y;

	if (cfg->map_width <= ZONE_WIDTH && cfg->map_height <= ZONE_HEIGHT)
	{
		cell_x = px_max / cfg->map_width;
		cell_y = py_max / cfg->map_height;
	}
	else
	{
		cell_x = px_max / ZONE_WIDTH;
		cell_y = py_max / ZONE_HEIGHT;
	}
	if (cell_x < cell_y)
		return (cell_x);
	return (cell_y);
}

void	draw_tile_line(t_tile_ctx *ctx, int y, int end_x)
{
	int	x;

	x = ctx->start_x;
	while (x < end_x)
	{
		if (x < (int)ft_strlen(ctx->game->map[y]))
			draw_map_tile(ctx, x, y);
		x++;
	}
}

void	init_minimap(t_game *game)
{
	int		cell_size;
	int		visible_w;
	int		visible_h;

	cell_size = calculate_cell_size(&game->config,
			WIDTH * MINIMAP_W_RATIO, HEIGHT * MINIMAP_H_RATIO);
	if (cell_size < 1)
		cell_size = 1;
	if (game->config.map_width <= ZONE_WIDTH)
		visible_w = game->config.map_width;
	else
		visible_w = ZONE_WIDTH;
	if (game->config.map_height <= ZONE_HEIGHT)
		visible_h = game->config.map_height;
	else
		visible_h = ZONE_HEIGHT;
	game->minimap.cell_size = cell_size;
	game->minimap.map_w = cell_size * visible_w;
	game->minimap.map_h = cell_size * visible_h;
	game->minimap.map_w = game->config.map_width;
	game->minimap.map_h = game->config.map_height;
	game->minimap.origin_x = 10;
	game->minimap.origin_y = 10;
	game->minimap.scale = (float)cell_size / (float)BLOCK;
}
