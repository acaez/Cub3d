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
	return (x * x + y * y);
}

static float	get_cos_correction(t_ray *r, float angle_diff)
{
	int		index;
	float	cos_diff;

	if (r->game->trigo.cos_table)
	{
		index = (int)((angle_diff + PI)
				* r->game->trigo.table_size / (2.0f * PI));
		if (index >= 0 && index < r->game->trigo.table_size)
			cos_diff = r->game->trigo.cos_table[index];
		else
			cos_diff = cosf(angle_diff);
	}
	else
		cos_diff = cosf(angle_diff);
	return (cos_diff);
}

float	fixed_dist(t_ray *r)
{
	float	delta_x;
	float	delta_y;
	float	angle_diff;
	float	dist;
	float	cos_diff;

	delta_x = r->ray_x - r->player->x;
	delta_y = r->ray_y - r->player->y;
	angle_diff = atan2f(delta_y, delta_x) - r->player->angle;
	while (angle_diff > PI)
		angle_diff -= 2.0f * PI;
	while (angle_diff < -PI)
		angle_diff += 2.0f * PI;
	cos_diff = get_cos_correction(r, angle_diff);
	dist = sqrtf(delta_x * delta_x + delta_y * delta_y) * cos_diff;
	return (dist);
}
