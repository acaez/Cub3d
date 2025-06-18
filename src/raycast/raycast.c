/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		index = y * game->size_line + x * (game->bpp / 8);
		game->data[index] = color & 0xFF;
		game->data[index + 1] = (color >> 8) & 0xFF;
		game->data[index + 2] = (color >> 16) & 0xFF;
	}
}

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

static float	compute_distance(float start, int map_pos, int step, float dir)
{
	float	result;

	result = map_pos - start / BLOCK;
	result += (1 - step) / 2.0f;
	result /= dir;
	return (result * BLOCK);
}

static int	get_texture_index(int side, float dx, float dy)
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

static void	setup_ray_ctx(t_game *game, t_ray_ctx *ctx)
{
	init_ray_direction(game, ctx->angle, &ctx->dx, &ctx->dy);
	ctx->map_x = (int)(ctx->start_x / BLOCK);
	ctx->map_y = (int)(ctx->start_y / BLOCK);
	ctx->delta_x = fabsf(1.0f / ctx->dx);
	ctx->delta_y = fabsf(1.0f / ctx->dy);
	init_step_and_dist(ctx->start_x, ctx->dx, ctx->delta_x,
		(t_step_ctx){ctx->map_x, &ctx->step_x, &ctx->side_x});
	init_step_and_dist(ctx->start_y, ctx->dy, ctx->delta_y,
		(t_step_ctx){ctx->map_y, &ctx->step_y, &ctx->side_y});
}

static void	finalize_ray_hit(t_ray_ctx *ctx, t_ray_hit *result)
{
	if (ctx->side == 0)
		ctx->wall_x = ctx->start_y + result->distance * ctx->dy / BLOCK;
	else
		ctx->wall_x = ctx->start_x + result->distance * ctx->dx / BLOCK;
	ctx->wall_x -= floorf(ctx->wall_x);
	result->wall_x = ctx->wall_x;
	result->tex_num = get_texture_index(ctx->side, ctx->dx, ctx->dy);
}

t_ray_hit	calculate_distance(t_game *game, t_ray_ctx *ctx)
{
	t_ray_hit	result;

	setup_ray_ctx(game, ctx);
	perform_dda(game, (t_dda_ctx){
		&ctx->map_x, &ctx->map_y, &ctx->side_x, &ctx->side_y,
		ctx->delta_x, ctx->delta_y, &ctx->step_x, &ctx->step_y,
		&ctx->side});
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

static void	limit_wall_bounds(int *start, int *end)
{
	if (*start < 0)
		*start = 0;
	if (*end > HEIGHT)
		*end = HEIGHT;
}

static int	compute_tex_x(t_ray_hit *hit, t_texture *tex, float angle)
{
	int	tex_x;

	tex_x = (int)(hit->wall_x * tex->width);
	if ((hit->side == 0 && cosf(angle) > 0)
		|| (hit->side == 1 && sinf(angle) < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
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

	ctx.ray = *ray;
	ctx.hit = calculate_distance(game, &ctx.ray);
	if (ctx.hit.distance < 0.1f)
		ctx.hit.distance = 0.1f;
	ctx.wall_height = (BLOCK * HEIGHT) / (ctx.hit.distance * 2.0f);
	if (ctx.wall_height > HEIGHT * 3)
		ctx.wall_height = HEIGHT * 3;
	ctx.wall_start = (HEIGHT - ctx.wall_height) / 2;
	ctx.wall_end = ctx.wall_start + ctx.wall_height;
	limit_wall_bounds(&ctx.wall_start, &ctx.wall_end);
	ctx.tex = &game->textures[ctx.hit.tex_num];
	ctx.tex_x = compute_tex_x(&ctx.hit, ctx.tex, ctx.ray.angle);
	draw_vertical_line(game, (t_draw_ctx){
		.tex = ctx.tex, .hit = &ctx.hit, .x = x,
		.wall_start = ctx.wall_start, .wall_end = ctx.wall_end,
		.tex_x = ctx.tex_x});
}

static int	load_texture_image(t_tex_ctx *ctx)
{
	t_texture	*tex;

	tex = &ctx->game->textures[ctx->index];
	tex->img = mlx_xpm_file_to_image(ctx->game->mlx, ctx->path,
			ctx->w, ctx->h);
	if (!tex->img)
		return (0);
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bpp,
			&tex->size_line,
			&tex->endian);
	tex->width = *ctx->w;
	tex->height = *ctx->h;
	return (1);
}

int	load_textures(t_game *game)
{
	int			w;
	int			h;
	t_tex_ctx	ctx;

	if (!game->config.no_path || !game->config.so_path
		|| !game->config.we_path || !game->config.ea_path)
		return (0);
	ctx = (t_tex_ctx){game, 0, game->config.no_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 1, game->config.so_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 2, game->config.we_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 3, game->config.ea_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	return (1);
}

static void	init_raycast(t_game *game, t_player *player)
{
	static int	textures_loaded = 0;

	if (!textures_loaded)
	{
		textures_loaded = load_textures(game);
		game->fraction = PI / 3 / WIDTH;
	}
	game->start_angle = player->angle - PI / 6;
}

static void	process_rays(t_game *game, t_player *player)
{
	t_ray_ctx	ray;
	float		angle;
	int			i;

	angle = game->start_angle;
	ray.start_x = player->x;
	ray.start_y = player->y;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = angle;
		cast_ray(game, &ray, i);
		angle += game->fraction;
		i++;
	}
}

int	raycast(t_game *game)
{
	t_player	*player;

	player = &game->player;
	limit_fps(game);
	init_raycast(game, player);
	if (game->debug_mode)
	{
		draw_debug_map(game);
		draw_debug_rays(game, player);
		return (0);
	}
	process_rays(game, player);
	return (0);
}
