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

int	get_wall_color(int side, int wall_dir)
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

void	calculate_wall_height(float perp_wall_dist, int *draw_points)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	float	projection;

	projection = 0.5f * (WIDTH / (2 * tan(PI / 6)));
	line_height = (int)(projection / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	draw_points[0] = draw_start;
	draw_points[1] = draw_end;
}
