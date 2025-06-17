/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:59:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 16:15:56 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

int	check_collision(t_config *config, float x, float y)
{
	int	map_x;
	int	map_y;

	if (!config || !config->map)
		return (1); // Considérer comme une collision si la config ou la map est NULL
	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (1); // Considérer comme une collision si hors limites
	if (!is_inside_map(config->map, map_y, map_x))
		return (1); // Considérer comme une collision si hors de la carte
	if (config->map[map_y] && !is_open_char(config->map[map_y][map_x]))
		return (1); // Collision si ce n'est pas un caractère ouvert (mur)
	return (0); // Pas de collision
}