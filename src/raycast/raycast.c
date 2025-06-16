/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 17:49:11 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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

static void	draw_wall_column(t_game *game, int x, float perp_wall_dist,
		t_ray wall)
{
	int	draw_points[2];
	int	wall_color;

	calculate_wall_height(perp_wall_dist, draw_points);
	wall_color = get_wall_color(wall.side, wall.wall_dir);
	draw_wall_segment(game, x, draw_points, wall_color);
}

static void	calculate_ray_direction(t_game *game, int x, float *ray_dir)
{
	float	camera_x;

	camera_x = 2.0f * x / WIDTH - 1.0f;
	ray_dir[0] = cos(game->player.angle) + camera_x * -sin(game->player.angle);
	ray_dir[1] = sin(game->player.angle) + camera_x * cos(game->player.angle);
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
	return (perp_wall_dist);
}

void	raycast(t_game *game)
{
	t_ray	wall;
	int		x;
	float	ray_dir[2];
	float	perp_wall_dist;

	if (!game || !game->map)
		return ;
	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_direction(game, x, ray_dir);
		game->ray.map_pos[0] = (int)(game->player.x / BLOCK);
		game->ray.map_pos[1] = (int)(game->player.y / BLOCK);
		dda_setup(game, ray_dir[0], ray_dir[1]);
		perform_dda(game);
		perp_wall_dist = calculate_perp_distance(game, ray_dir);
		wall.side = game->ray.hit_info[2];
		wall.wall_dir = game->ray.hit_info[3];
		draw_wall_column(game, x, perp_wall_dist, wall);
		x++;
	}
}
