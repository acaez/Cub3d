/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:59:48 by acaes             #+#    #+#             */
/*   Updated: 2025/06/27 10:59:48 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	get_texture_color(t_texture *tex, float wall_x, float wall_y)
{
	int	tex_x;
	int	tex_y;
	int	color;

	if (!tex || !tex->data)
		return (0x8B4513);
	tex_x = (int)(wall_x * tex->width);
	tex_y = (int)(wall_y * tex->height);
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	color = *(int *)(tex->data + (tex_y * tex->size_line
				+ tex_x * (tex->bpp / 8)));
	return (color);
}

static void	draw_sky_floor(t_game *game, int x, int wall_start, int wall_end)
{
	int	y;

	y = 0;
	while (y < wall_start)
	{
		put_pixel(game, x, y, game->config.sky_color);
		y++;
	}
	y = wall_end;
	while (y < game->window_height)
	{
		put_pixel(game, x, y, game->config.floor_color);
		y++;
	}
}

static void	draw_wall(t_game *game, int x, t_ray *ray, int wall_params[4])
{
	int			y;
	float		wall_y;
	t_texture	*texture;

	texture = get_wall_texture(game, ray->wall_direction);
	y = wall_params[0];
	while (y < wall_params[1])
	{
		wall_y = (float)(y - wall_params[0]) / wall_params[2];
		put_pixel(game, x, y, get_texture_color(texture,
				ray->wall_hit_x, wall_y));
		y++;
	}
}

void	draw_texture(t_game *game, int x, t_ray *ray, float distance)
{
	int		wall_params[4];
	float	corrected_distance;
	float	ray_angle;

	ray_angle = game->player.angle - (30 * PI / 180)
		+ x * (60 * PI / 180) / game->window_width;
	corrected_distance = distance * cos(game->player.angle - ray_angle);
	wall_params[2] = (int)(BLOCK * game->window_height / corrected_distance);
	wall_params[0] = (game->window_height - wall_params[2]) / 2;
	wall_params[1] = wall_params[0] + wall_params[2];
	draw_sky_floor(game, x, wall_params[0], wall_params[1]);
	draw_wall(game, x, ray, wall_params);
}
