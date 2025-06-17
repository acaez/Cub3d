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


float	fixed_dist(t_ray *r)
{
	float	delta_x;
	float	delta_y;
	float	angle_diff;
	float	cos_diff;
	float	dist;

	delta_x = r->ray_x - r->player->x;
	delta_y = r->ray_y - r->player->y;
	angle_diff = atan2f(delta_y, delta_x) - r->player->angle;
	while (angle_diff > PI)
		angle_diff -= 2.0f * PI;
	while (angle_diff < -PI)
		angle_diff += 2.0f * PI;
	if (r->game->trigo.cos_table)
	{
		int index = (int)((angle_diff + PI) * r->game->trigo.table_size / (2.0f * PI));
		if (index >= 0 && index < r->game->trigo.table_size)
			cos_diff = r->game->trigo.cos_table[index];
		else
			cos_diff = cosf(angle_diff);
	}
	else
		cos_diff = cosf(angle_diff);
	dist = sqrtf(delta_x * delta_x + delta_y * delta_y) * cos_diff;
	return (dist);
}

void	get_trigo_value(t_trigo *trigo, float angle, float *cos_val, float *sin_val)
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

int	check_collision(t_config *config, float x, float y)
{
	int		map_x;
	int		map_y;
	float	margin;

	if (!config || !config->map)
		return (1);
	
	// Marge de sécurité pour éviter de coller aux murs (en pourcentage du bloc)
	margin = BLOCK * 0.1;
	
	// Vérifier la position directe
	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (!is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	
	// Vérifier les positions avec marge (autour du joueur)
	// Vérifier à droite
	map_x = (int)((x + margin) / BLOCK);
	if (map_x < 0 || map_y < 0 || !is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	
	// Vérifier à gauche
	map_x = (int)((x - margin) / BLOCK);
	if (map_x < 0 || map_y < 0 || !is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	
	// Vérifier en haut
	map_x = (int)(x / BLOCK);
	map_y = (int)((y - margin) / BLOCK);
	if (map_x < 0 || map_y < 0 || !is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	
	// Vérifier en bas
	map_y = (int)((y + margin) / BLOCK);
	if (map_x < 0 || map_y < 0 || !is_inside_map(config->map, map_y, map_x))
		return (1);
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1);
	
	return (0);
}
