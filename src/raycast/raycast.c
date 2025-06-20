/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 14:26:15 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_raycast(t_game *game, t_player *player)
{
	static int	textures_loaded = 0;

	if (!textures_loaded)
	{
		textures_loaded = load_textures(game);
		game->fraction = PI / 3 / WIDTH;
	}
	game->start_angle = player->angle - PI / 6;
	while (player->angle < 0)
		player->angle += 2 * PI;
	while (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

static void	process_rays(t_game *game, t_player *player)
{
	t_ray_ctx	ray;
	float		angle;
	int			i;

	angle = game->start_angle;
	ray.start_x = player->x;
	ray.start_y = player->y;
	i = 0;
	while (i < WIDTH)
	{
		ray.angle = angle;
		while (ray.angle < 0)
			ray.angle += 2 * PI;
		while (ray.angle >= 2 * PI)
			ray.angle -= 2 * PI;
		cast_ray(game, &ray, i);
		angle += game->fraction;
		i++;
	}
}

int	raycast(t_game *game)
{
	t_player	*player;

	player = &game->player;
	init_raycast(game, player);
	if (game->debug_mode)
	{
		draw_debug_map(game);
		draw_debug_rays(game, player);
		return (0);
	}
	process_rays(game, player);
	return (0);
}
