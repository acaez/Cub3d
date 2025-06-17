/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:45:53 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	draw_debug_ray_point(t_game *game, float ray_x, float ray_y,
	t_debug_map *dm)
{
	float	map_ray_x;
	float	map_ray_y;

	map_ray_x = dm->offset_x + ray_x / BLOCK * dm->scale;
	map_ray_y = dm->offset_y + ray_y / BLOCK * dm->scale;
	if (map_ray_x >= 0 && map_ray_x < WIDTH
		&& map_ray_y >= 0 && map_ray_y < HEIGHT)
	{
		put_pixel(game, map_ray_x, map_ray_y, 0xFF0000);
		return (0);
	}
	return (1);
}

static void	cast_debug_ray(t_game *game, t_player *player, float ray_angle,
	t_debug_map *dm)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	step;

	step = 0.5;
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	ray_x = player->x;
	ray_y = player->y;
	while (!check_collision(&game->config, ray_x, ray_y))
	{
		ray_x += cos_angle * step;
		ray_y += sin_angle * step;
		if (draw_debug_ray_point(game, ray_x, ray_y, dm))
			break ;
	}
	draw_debug_impact(game, ray_x, ray_y, dm);
}

void	draw_debug_rays(t_game *game, t_player *player)
{
	float		fraction;
	float		start_x;
	int			i;
	t_debug_map	dm;

	dm.scale = calculate_debug_scale(game, &dm.offset_x, &dm.offset_y);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		if (i % 10 == 0)
			cast_debug_ray(game, player, start_x, &dm);
		start_x += fraction;
		i++;
	}
}

void	draw_debug_map(t_game *game)
{
	int			x;
	int			y;
	t_debug_map	dm;

	draw_debug_background(game);
	dm.scale = calculate_debug_scale(game, &dm.offset_x, &dm.offset_y);
	y = 0;
	while (y < game->config.map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map[y]))
		{
			draw_debug_cell(game, x, y, &dm);
			x++;
		}
		y++;
	}
	draw_debug_player(game, &dm);
}
