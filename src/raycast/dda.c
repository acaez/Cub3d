/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 12:00:00 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	setup_x_direction(t_game *game, float ray_dir_x)
{
	int	map_x;

	map_x = game->ray.map_pos[0];
	if (ray_dir_x < 0)
	{
		game->ray.side_dist[0] = (game->player.x / BLOCK - map_x)
			* game->ray.delta_dist[0];
		game->ray.side_dist[2] = -1;
	}
	else
	{
		game->ray.side_dist[0] = (map_x + 1.0 - game->player.x / BLOCK)
			* game->ray.delta_dist[0];
		game->ray.side_dist[2] = 1;
	}
}

static void	setup_y_direction(t_game *game, float ray_dir_y)
{
	int	map_y;

	map_y = game->ray.map_pos[1];
	if (ray_dir_y < 0)
	{
		game->ray.side_dist[1] = (game->player.y / BLOCK - map_y)
			* game->ray.delta_dist[1];
		game->ray.side_dist[3] = -1;
	}
	else
	{
		game->ray.side_dist[1] = (map_y + 1.0 - game->player.y / BLOCK)
			* game->ray.delta_dist[1];
		game->ray.side_dist[3] = 1;
	}
}

void	dda_setup(t_game *game, float ray_dir_x, float ray_dir_y)
{
	if (ray_dir_x == 0)
		game->ray.delta_dist[0] = 1e30;
	else
		game->ray.delta_dist[0] = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		game->ray.delta_dist[1] = 1e30;
	else
		game->ray.delta_dist[1] = fabs(1.0 / ray_dir_y);
	setup_x_direction(game, ray_dir_x);
	setup_y_direction(game, ray_dir_y);
}

static void	step_ray(t_game *game, int *side)
{
	if (game->ray.side_dist[0] < game->ray.side_dist[1])
	{
		game->ray.side_dist[0] += game->ray.delta_dist[0];
		game->ray.map_pos[0] += (int)game->ray.side_dist[2];
		*side = 0;
	}
	else
	{
		game->ray.side_dist[1] += game->ray.delta_dist[1];
		game->ray.map_pos[1] += (int)game->ray.side_dist[3];
		*side = 1;
	}
}

void	perform_dda(t_game *game)
{
	int	hit;
	int	side;

	hit = 0;
	while (!hit)
	{
		step_ray(game, &side);
		hit = touch_wall(game, game->ray.map_pos[0], game->ray.map_pos[1]);
	}
	game->ray.hit_info[0] = game->ray.map_pos[0];
	game->ray.hit_info[1] = game->ray.map_pos[1];
	game->ray.hit_info[2] = side;
	if (game->ray.side_dist[side * 2 + 2] > 0)
		game->ray.hit_info[3] = 1;
	else
		game->ray.hit_info[3] = 0;
}
