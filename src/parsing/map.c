/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:49 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:31:42 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	update_player_zone(t_game *game, t_minimap *m)
{
	int	px;
	int	py;

	px = (int)(game->player.x / BLOCK);
	py = (int)(game->player.y / BLOCK);
	m->zone_x = px / ZONE_WIDTH;
	m->zone_y = py / ZONE_HEIGHT;
}

static void	draw_map_tile(t_tile_ctx *ctx, int x, int y)
{
	t_square	sq;
	char		cell;

	cell = ctx->game->map[y][x];
	if (cell == '1')
		sq.color = 0xAAAAAA;
	else
		sq.color = 0x222222;
	sq.x = ctx->minimap->origin_x + (x - ctx->start_x)
		* ctx->minimap->cell_size;
	sq.y = ctx->minimap->origin_y + (y - ctx->start_y)
		* ctx->minimap->cell_size;
	sq.size = ctx->minimap->cell_size;
	draw_filled_square(ctx->game, sq);
}

static void	draw_map_tiles(t_game *game, t_minimap *m)
{
	t_tile_ctx	ctx;
	int			end_x;
	int			end_y;
	int			y;
	int			x;

	ctx.game = game;
	ctx.minimap = m;
	ctx.start_x = m->zone_x * ZONE_WIDTH;
	ctx.start_y = m->zone_y * ZONE_HEIGHT;
	end_x = ctx.start_x + ZONE_WIDTH;
	end_y = ctx.start_y + ZONE_HEIGHT;
	if (end_x > m->map_w)
		end_x = m->map_w;
	if (end_y > m->map_h)
		end_y = m->map_h;
	y = ctx.start_y;
	while (y < end_y)
	{
		x = ctx.start_x;
		while (x < end_x)
			draw_map_tile(&ctx, x++, y);
		y++;
	}
}

static void	draw_player_dot(t_game *game, t_minimap *m)
{
	int			cell_px;
	int			cell_py;
	int			start_x;
	int			start_y;
	t_square	sq;

	cell_px = (int)(game->player.x / BLOCK);
	cell_py = (int)(game->player.y / BLOCK);
	start_x = m->zone_x * ZONE_WIDTH;
	start_y = m->zone_y * ZONE_HEIGHT;
	sq.x = m->origin_x + (int)((cell_px - start_x) * m->cell_size
			+ (game->player.x - cell_px * BLOCK) * m->scale) - 2;
	sq.y = m->origin_y + (int)((cell_py - start_y) * m->cell_size
			+ (game->player.y - cell_py * BLOCK) * m->scale) - 2;
	sq.size = 4;
	sq.color = 0xFF0000;
	draw_filled_square(game, sq);
}

void	draw_minimap(t_game *game)
{
	t_minimap	m;

	init_minimap(game, &m);
	update_player_zone(game, &m);
	draw_map_tiles(game, &m);
	draw_player_dot(game, &m);
}
