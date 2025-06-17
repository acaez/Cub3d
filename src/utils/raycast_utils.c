/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:59:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:53:30 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

// Too much calculation here per frame per ray !!!!!!
float	fixed_dist(t_ray *r)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = r->ray_x - r->player->x;
	delta_y = r->ray_y - r->player->y;
	angle = atan2f(delta_y, delta_x) - r->player->angle;
	fix_dist = sqrtf(delta_x * delta_x + delta_y * delta_y) * cosf(angle);
	return (fix_dist);
}

int	check_collision(t_config *config, float x, float y)
{
	int	map_x;
	int	map_y;

	if (!config || !config->map)
		return (1);
	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (!is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	return (0);
}
