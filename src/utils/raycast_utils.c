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

void	get_trigo_value(t_trigo *trigo, float angle, float *cos_val,
			float *sin_val)
{
	int	index;

	while (angle < 0)
		angle += 2.0f * PI;
	while (angle >= 2.0f * PI)
		angle -= 2.0f * PI;
	index = (int)(angle * (float)trigo->table_size / (2.0f * PI));
	if (index >= trigo->table_size)
		index = trigo->table_size - 1;
	*cos_val = trigo->cos_table[index];
	*sin_val = trigo->sin_table[index];
}

void	limit_fps(t_game *game)
{
	clock_t		current_time;
	long		elapsed_us;
	long		sleep_time;

	current_time = clock();
	elapsed_us = ((current_time - game->last_frame) * 1000000) / CLOCKS_PER_SEC;
	if (elapsed_us < (1000000 / 60))
	{
		sleep_time = (1000000 / 60) - elapsed_us;
		usleep(sleep_time);
	}
	game->last_frame = clock();
}

static int	is_blocked_at(t_config *config, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (!is_inside_map(config->map, map_y, map_x))
		return (1);
	if (!is_open_char(config->map[map_y][map_x]))
		return (1);
	return (0);
}

int	check_collision(t_config *config, float x, float y)
{
	float	margin;

	if (!config || !config->map)
		return (1);
	margin = BLOCK * 0.1;
	if (is_blocked_at(config, x, y))
		return (1);
	if (is_blocked_at(config, x + margin, y))
		return (1);
	if (is_blocked_at(config, x - margin, y))
		return (1);
	if (is_blocked_at(config, x, y + margin))
		return (1);
	if (is_blocked_at(config, x, y - margin))
		return (1);
	return (0);
}
