/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_ray_direction(t_game *game, float angle, float *dx, float *dy)
{
	if (game->trigo.cos_table)
		get_trigo_value(&game->trigo, angle, dx, dy);
	else
	{
		*dx = cosf(angle);
		*dy = sinf(angle);
	}
}

static void	init_step_and_dist(float start, float dir, float delta,
	t_step_ctx ctx)
{
	if (dir < 0)
	{
		*(ctx.step) = -1;
		*(ctx.side_dist) = (start / BLOCK - ctx.map_pos) * delta;
	}
	else
	{
		*(ctx.step) = 1;
		*(ctx.side_dist) = (ctx.map_pos + 1.0f - start / BLOCK) * delta;
	}
}

float	compute_distance(float start, int map_pos, int step, float dir)
{
	float	result;

	result = map_pos - start / BLOCK;
	result += (1 - step) / 2.0f;
	result /= dir;
	return (result * BLOCK);
}

int	get_texture_index(int side, float dx, float dy)
{
	if (side == 0)
	{
		if (dx < 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (dy < 0)
			return (0);
		else
			return (1);
	}
}

void	setup_ray_ctx(t_game *game, t_ray_ctx *ctx)
{
	init_ray_direction(game, ctx->angle, &ctx->dx, &ctx->dy);
	ctx->map_x = (int)(ctx->start_x / BLOCK);
	ctx->map_y = (int)(ctx->start_y / BLOCK);
	ctx->delta_x = fabsf(1.0f / ctx->dx);
	ctx->delta_y = fabsf(1.0f / ctx->dy);
	step_ctx_x.map_pos = ctx->map_x;
	step_ctx_x.step = &ctx->step_x;
	step_ctx_x.side_dist = &ctx->side_x;
	step_ctx_y.map_pos = ctx->map_y;
	step_ctx_y.step = &ctx->step_y;
	step_ctx_y.side_dist = &ctx->side_y;
	init_step_and_dist(ctx->start_x, ctx->dx, ctx->delta_x, step_ctx_x);
	init_step_and_dist(ctx->start_y, ctx->dy, ctx->delta_y, step_ctx_y);
}
