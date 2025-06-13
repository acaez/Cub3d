/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:59:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 15:59:03 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

float	distance(float dx, float dy)
{
	return (sqrt(dx * dx + dy * dy));
}

bool	touch_wall(t_game *game, float px, float py)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (y < 0 || !game->map[y])
		return (true);
	if (x < 0 || x >= (int)ft_strlen(game->map[y]))
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}
