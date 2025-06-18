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
	int map_pos, int *step, float *side_dist)
{
	if (dir < 0)
	{
		*step = -1;
		*side_dist = (start / BLOCK - map_pos) * delta;
	}
	else
	{
		*step = 1;
		*side_dist = (map_pos + 1.0f - start / BLOCK) * delta;
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

static void	perform_dda(t_game *game, int *map_x, int *map_y,
	float *side_x, float *side_y, float delta_x, float delta_y,
	int *step_x, int *step_y, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (*side_x < *side_y)
		{
			*side_x += delta_x;
			*map_x += *step_x;
			*side = 0;
		}
		else
		{
			*side_y += delta_y;
			*map_y += *step_y;
			*side = 1;
		}
		hit = is_blocking_cell(game, *map_x, *map_y);
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

t_ray_hit	calculate_distance(t_game *game, float start_x, float start_y, float angle)
{
	t_ray_hit	result;
	float		dx, dy;
	int			map_x, map_y;
	float		delta_x, delta_y;
	int			step_x, step_y;
	float		side_x, side_y;
	int			side;
	float		wall_x;

	init_ray_direction(game, angle, &dx, &dy);
	map_x = (int)(start_x / BLOCK);
	map_y = (int)(start_y / BLOCK);
	delta_x = fabsf(1.0f / dx);
	delta_y = fabsf(1.0f / dy);
	init_step_and_dist(start_x, dx, delta_x, map_x, &step_x, &side_x);
	init_step_and_dist(start_y, dy, delta_y, map_y, &step_y, &side_y);
	perform_dda(game, &map_x, &map_y, &side_x, &side_y,
		delta_x, delta_y, &step_x, &step_y, &side);
	if (side == 0)
		result.distance = compute_distance(start_x, map_x, step_x, dx);
	else
		result.distance = compute_distance(start_y, map_y, step_y, dy);
	result.side = side;
	if (side == 0)
		wall_x = start_y + result.distance * dy / BLOCK;
	else
		wall_x = start_x + result.distance * dx / BLOCK;
	wall_x -= floorf(wall_x);
	result.wall_x = wall_x;
	result.tex_num = get_texture_index(side, dx, dy);
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
	int tex_x;

	tex_x = (int)(hit->wall_x * tex->width);
	if ((hit->side == 0 && cosf(angle) > 0)
		|| (hit->side == 1 && sinf(angle) < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_vertical_line(t_game *game, t_texture *tex,
		t_ray_hit *hit, int x, int wall_start, int wall_end, int tex_x)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (float)tex->height / (wall_end - wall_start);
	tex_pos = (wall_start - (HEIGHT - (wall_end - wall_start)) / 2) * step;
	y = wall_start;
	while (y < wall_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = *(int *)(tex->data + tex_y * tex->size_line + tex_x
				* (tex->bpp / 8));
		if (hit->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(game, x, y, color);
		y++;
	}
}

void	cast_ray(t_game *game, t_player *player, float angle, int x)
{
	t_ray_hit	hit;
	t_texture	*tex;
	float		wall_height;
	int			wall_start;
	int			wall_end;
	int			tex_x;

	hit = calculate_distance(game, player->x, player->y, angle);
	if (hit.distance < 0.1f)
		hit.distance = 0.1f;
	wall_height = (BLOCK * HEIGHT) / (hit.distance * 2.0f);
	if (wall_height > HEIGHT * 3)
		wall_height = HEIGHT * 3;
	wall_start = (HEIGHT - wall_height) / 2;
	wall_end = wall_start + wall_height;
	limit_wall_bounds(&wall_start, &wall_end);
	tex = &game->textures[hit.tex_num];
	tex_x = compute_tex_x(&hit, tex, angle);
	draw_vertical_line(game, tex, &hit, x, wall_start, wall_end, tex_x);
}

static int	load_texture_image(t_game *game, int i, char *path, int *w, int *h)
{
	game->textures[i].img = mlx_xpm_file_to_image(game->mlx, path, w, h);
	if (!game->textures[i].img)
		return (0);
	game->textures[i].data = mlx_get_data_addr(game->textures[i].img,
			&game->textures[i].bpp,
			&game->textures[i].size_line,
			&game->textures[i].endian);
	game->textures[i].width = *w;
	game->textures[i].height = *h;
	return (1);
}

int	load_textures(t_game *game)
{
	int	w;
	int	h;

	if (!game->config.no_path || !game->config.so_path
		|| !game->config.we_path || !game->config.ea_path)
		return (0);
	if (!load_texture_image(game, 0, game->config.no_path, &w, &h))
		return (0);
	if (!load_texture_image(game, 1, game->config.so_path, &w, &h))
		return (0);
	if (!load_texture_image(game, 2, game->config.we_path, &w, &h))
		return (0);
	if (!load_texture_image(game, 3, game->config.ea_path, &w, &h))
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
	float	angle;
	int		i;

	angle = game->start_angle;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(game, player, angle, i);
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
