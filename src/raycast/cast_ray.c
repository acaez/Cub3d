/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	compute_tex_x(t_ray_hit *hit, t_texture *tex, float angle)
{
	int	tex_x;

	tex_x = (int)(hit->wall_x * tex->width);
	if ((hit->side == 0 && cosf(angle) > 0)
		|| (hit->side == 1 && sinf(angle) < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	limit_wall_bounds(int *start, int *end)
{
	if (*start < 0)
		*start = 0;
	if (*end > HEIGHT)
		*end = HEIGHT;
}

static void	draw_vertical_line(t_game *game, t_draw_ctx ctx)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (float)ctx.tex->height / (ctx.wall_end - ctx.wall_start);
	tex_pos = (ctx.wall_start - (HEIGHT - (ctx.wall_end - ctx.wall_start)) / 2)
		* step;
	y = ctx.wall_start;
	while (y < ctx.wall_end)
	{
		tex_y = (int)tex_pos & (ctx.tex->height - 1);
		tex_pos += step;
		color = *(int *)(ctx.tex->data + tex_y * ctx.tex->size_line + ctx.tex_x
				* (ctx.tex->bpp / 8));
		if (ctx.hit->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(game, ctx.x, y, color);
		y++;
	}
}

void	cast_ray(t_game *game, t_ray_ctx *ray, int x)
{
	t_cast_ctx	ctx;
	t_draw_ctx	draw_ctx;

	ctx.ray = *ray;
	ctx.hit = calculate_distance(game, &ctx.ray);
	if (ctx.hit.distance < 0.1f)
		ctx.hit.distance = 0.1f;
	angle_diff = ctx.ray.angle - game->player.angle;
	corrected_distance = ctx.hit.distance * cosf(angle_diff);
	ctx.wall_height = (BLOCK * HEIGHT) / (ctx.hit.distance * 2.0f);
	if (ctx.wall_height > HEIGHT * 3)
		ctx.wall_height = HEIGHT * 3;
	ctx.wall_start = (HEIGHT - ctx.wall_height) / 2;
	ctx.wall_end = ctx.wall_start + ctx.wall_height;
	limit_wall_bounds(&ctx.wall_start, &ctx.wall_end);
	ctx.tex = &game->textures[ctx.hit.tex_num];
	ctx.tex_x = compute_tex_x(&ctx.hit, ctx.tex, ctx.ray.angle);
	draw_ctx.tex = ctx.tex;
	draw_ctx.hit = &ctx.hit;
	draw_ctx.x = x;
	draw_ctx.wall_start = ctx.wall_start;
	draw_ctx.wall_end = ctx.wall_end;
	draw_ctx.tex_x = ctx.tex_x;
	draw_vertical_line(game, draw_ctx);
}
