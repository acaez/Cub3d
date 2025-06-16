/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 12:00:00 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	get_wall_color(int side, int wall_dir)
{
	if (side == 0)
	{
		if (wall_dir == 1)
			return (0xAA0000);
		return (0x880000);
	}
	else
	{
		if (wall_dir == 1)
			return (0xFF0000);
		return (0xDD0000);
	}
}

static void	draw_wall_segment(t_game *game, int x, int *draw_points,
		int wall_color)
{
	int	y;
	int	draw_start;
	int	draw_end;

	draw_start = draw_points[0];
	draw_end = draw_points[1];
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel(game, x, y, wall_color);
		y++;
	}
}

static void	calculate_wall_height(float perp_wall_dist, int *draw_points)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	draw_points[0] = draw_start;
	draw_points[1] = draw_end;
}

static void	draw_wall_column(t_game *game, int x, float perp_wall_dist,
		int side, int wall_dir)
{
	int	draw_points[2];
	int	wall_color;

	calculate_wall_height(perp_wall_dist, draw_points);
	wall_color = get_wall_color(side, wall_dir);
	draw_wall_segment(game, x, draw_points, wall_color);
}

static void	draw_debug_pixel(t_game *game, float px, float py,
		int map_x, int map_y)
{
	if ((int)(px / BLOCK) == map_x && (int)(py / BLOCK) == map_y)
		put_pixel(game, px, py, 0xFF0000);
	else
		put_pixel(game, px, py, 0x00FF00);
}

static void	draw_ray_segment(t_game *game, float ray_angle,
		float dist, int map_x, int map_y)
{
	int		i;
	float	px;
	float	py;

	i = 0;
	while (i < dist * BLOCK)
	{
		px = game->player.x + cos(ray_angle) * i / 20.0;
		py = game->player.y + sin(ray_angle) * i / 20.0;
		draw_debug_pixel(game, px, py, map_x, map_y);
		i++;
	}
}

static void	draw_debug_ray(t_game *game, int x)
{
	float	ray_angle;
	int		map_x;
	int		map_y;

	if (!game->debug_mode || x % 50 != 0)
		return ;
	ray_angle = game->player.angle - (PI / 6) + ((float)x / WIDTH) * (PI / 3);
	map_x = game->ray.hit_info[0];
	map_y = game->ray.hit_info[1];
	draw_ray_segment(game, ray_angle, 20, map_x, map_y);
}

static void	calculate_ray_direction(t_game *game, int x, float *ray_dir)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray_dir[0] = cos(game->player.angle) + sin(game->player.angle) * camera_x;
	ray_dir[1] = sin(game->player.angle) - cos(game->player.angle) * camera_x;
}

static float	calculate_perp_distance(t_game *game, float *ray_dir)
{
	float	perp_wall_dist;
	int		hit_side;
	int		hit_x;
	int		hit_y;

	hit_side = game->ray.hit_info[2];
	hit_x = game->ray.hit_info[0];
	hit_y = game->ray.hit_info[1];
	if (hit_side == 0)
	{
		perp_wall_dist = (hit_x - game->player.x / BLOCK
				+ (1 - (int)game->ray.side_dist[2]) / 2) / ray_dir[0];
	}
	else
	{
		perp_wall_dist = (hit_y - game->player.y / BLOCK
				+ (1 - (int)game->ray.side_dist[3]) / 2) / ray_dir[1];
	}
	return (perp_wall_dist * BLOCK);
}

void	raycast(t_game *game)
{
	int		x;
	float	ray_dir[2];
	float	perp_wall_dist;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_direction(game, x, ray_dir);
		game->ray.map_pos[0] = (int)(game->player.x / BLOCK);
		game->ray.map_pos[1] = (int)(game->player.y / BLOCK);
		dda_setup(game, ray_dir[0], ray_dir[1]);
		perform_dda(game);
		perp_wall_dist = calculate_perp_distance(game, ray_dir);
		draw_wall_column(game, x, perp_wall_dist,
			game->ray.hit_info[2], game->ray.hit_info[3]);
		draw_debug_ray(game, x);
		x++;
	}
}
