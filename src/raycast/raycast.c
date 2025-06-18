/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		index = y * game->size_line + x * (game->bpp / 8);
		game->data[index] = color & 0xFF;
		game->data[index + 1] = (color >> 8) & 0xFF;
		game->data[index + 2] = (color >> 16) & 0xFF;
	}
}

static void	init_raycast(t_game *game, t_player *player)
{
	static int	textures_loaded = 0;

	if (!textures_loaded)
	{
		textures_loaded = load_textures(game);
		game->fraction = PI / 3 / WIDTH;
	}
	game->start_angle = player->angle - PI / 6;
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
		cast_ray(game, &ray, i);
		angle += game->fraction;
		i++;
	}
}

int	raycast(t_game *game)
{
	t_player	*player;

	player = &game->player;
	limit_fps(game);
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
