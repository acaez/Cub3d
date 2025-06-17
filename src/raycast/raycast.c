/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:00:00 by matsauva         ###   ########.fr       */
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

static void	calculate_wall_height(t_ray *r)
{
	float	dist;

	if (r->steps >= r->max_steps)
		dist = WIDTH;
	else
	{
		dist = fixed_dist(r->player->x, r->player->y, r->ray_x, r->ray_y, r->game);
		if (dist <= 0.1f)
			dist = 0.1f;
	}
	r->height = (BLOCK / dist) * ((float)WIDTH / 2);
	if (r->height > HEIGHT * 3)
		r->height = HEIGHT * 3;
}

static void	draw_wall_line(t_ray *r)
{
	int	start_y;
	int	end_y;

	start_y = (HEIGHT - r->height) / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = start_y + r->height;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	while (start_y < end_y)
	{
		put_pixel(r->game, r->i, start_y, r->wall_color);
		start_y++;
	}
}

static void	cast_ray(t_game *game, t_player *player, float angle, int i)
{
	t_ray	r;

	r.game = game;
	r.player = player;
	r.i = i;
	r.wall_color = 0xFFFFFF;
	r.ray_x = player->x;
	r.ray_y = player->y;
	r.cos_angle = cos(angle) * 0.5;
	r.sin_angle = sin(angle) * 0.5;
	r.max_steps = 1000;
	r.steps = 0;
	while (r.steps < r.max_steps)
	{
		r.ray_x += r.cos_angle;
		r.ray_y += r.sin_angle;
		r.steps++;
		if (check_collision(&game->config, r.ray_x, r.ray_y))
			break ;
	}
	calculate_wall_height(&r);
	draw_wall_line(&r);
}

int	raycast(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	if (game->debug_mode)
	{
		draw_debug_map(game);
		draw_debug_rays(game, player);
		return (0);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(game, player, start_x, i);
		start_x += fraction;
		i++;
	}
	return (0);
}
