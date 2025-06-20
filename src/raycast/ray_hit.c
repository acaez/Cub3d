/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	is_blocking_cell(t_game *game, int mx, int my)
{
	if (mx < 0 || my < 0)
		return (1);
	if (my >= game->config.map_height)
		return (1);
	if (mx >= (int)ft_strlen(game->config.map[my]))
		return (1);
	if (game->config.map[my][mx] == '1')
		return (1);
	return (0);
}

static void	perform_dda(t_game *game, t_dda_ctx ctx)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (*(ctx.side_x) < *(ctx.side_y))
		{
			*(ctx.side_x) += ctx.delta_x;
			*(ctx.map_x) += *(ctx.step_x);
			*(ctx.side) = 0;
		}
		else
		{
			*(ctx.side_y) += ctx.delta_y;
			*(ctx.map_y) += *(ctx.step_y);
			*(ctx.side) = 1;
		}
		hit = is_blocking_cell(game, *(ctx.map_x), *(ctx.map_y));
	}
}

static void	finalize_ray_hit(t_ray_ctx *ctx, t_ray_hit *result)
{
	float	hit_x;
	float	hit_y;

	hit_x = ctx->start_x + result->distance * ctx->dx / BLOCK;
	hit_y = ctx->start_y + result->distance * ctx->dy / BLOCK;
	if (ctx->side == 0)
		ctx->wall_x = hit_y - floorf(hit_y);
	else
		ctx->wall_x = hit_x - floorf(hit_x);
	result->wall_x = ctx->wall_x;
	result->tex_num = get_texture_index(ctx->side, ctx->dx, ctx->dy);
}

t_ray_hit	calculate_distance(t_game *game, t_ray_ctx *ctx)
{
	t_ray_hit	result;
	t_dda_ctx	dda_ctx;

	setup_ray_ctx(game, ctx);
	dda_ctx.map_x = &ctx->map_x;
	dda_ctx.map_y = &ctx->map_y;
	dda_ctx.side_x = &ctx->side_x;
	dda_ctx.side_y = &ctx->side_y;
	dda_ctx.delta_x = ctx->delta_x;
	dda_ctx.delta_y = ctx->delta_y;
	dda_ctx.step_x = &ctx->step_x;
	dda_ctx.step_y = &ctx->step_y;
	dda_ctx.side = &ctx->side;
	perform_dda(game, dda_ctx);
	if (ctx->side == 0)
		result.distance = compute_distance(ctx->start_x, ctx->map_x,
				ctx->step_x, ctx->dx);
	else
		result.distance = compute_distance(ctx->start_y, ctx->map_y,
				ctx->step_y, ctx->dy);
	result.side = ctx->side;
	finalize_ray_hit(ctx, &result);
	return (result);
}
