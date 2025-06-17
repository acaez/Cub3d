/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:44:04 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_debug_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	calculate_debug_scale(t_game *game, int *offset_x, int *offset_y)
{
	int	map_width;
	int	map_height;
	int	scale_x;
	int	scale_y;
	int	scale;

	map_width = game->config.map_width;
	map_height = game->config.map_height;
	scale_x = WIDTH / map_width;
	scale_y = HEIGHT / map_height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	*offset_x = (WIDTH - map_width * scale) / 2;
	*offset_y = (HEIGHT - map_height * scale) / 2;
	return (scale);
}

void	draw_debug_cell(t_game *game, int x, int y, t_debug_map *dm)
{
	int	i;
	int	j;
	int	color;

	if (game->config.map[y][x] == '1')
		color = 0xFFFFFF;
	else
		color = 0x333333;
	i = 0;
	while (i < dm->scale)
	{
		j = 0;
		while (j < dm->scale)
		{
			put_pixel(game, dm->offset_x + x * dm->scale + i,
				dm->offset_y + y * dm->scale + j, color);
			j++;
		}
		i++;
	}
}

void	draw_debug_player(t_game *game, t_debug_map *dm)
{
	int	player_x;
	int	player_y;
	int	player_size;
	int	i;
	int	j;

	player_x = dm->offset_x + (int)(game->player.x / BLOCK * dm->scale);
	player_y = dm->offset_y + (int)(game->player.y / BLOCK * dm->scale);
	player_size = dm->scale / 4;
	if (player_size < 4)
		player_size = 4;
	i = -player_size / 2;
	while (i < player_size / 2)
	{
		j = -player_size / 2;
		while (j < player_size / 2)
		{
			put_pixel(game, player_x + i, player_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	draw_debug_impact(t_game *game, float ray_x, float ray_y,
	t_debug_map *dm)
{
	float	impact_x;
	float	impact_y;
	int		i;
	int		j;

	impact_x = dm->offset_x + ray_x / BLOCK * dm->scale;
	impact_y = dm->offset_y + ray_y / BLOCK * dm->scale;
	if (impact_x >= 0 && impact_x < WIDTH && impact_y >= 0 && impact_y < HEIGHT)
	{
		i = -1;
		while (i <= 1)
		{
			j = -1;
			while (j <= 1)
			{
				put_pixel(game, impact_x + i, impact_y + j, 0xFFFF00);
				j++;
			}
			i++;
		}
	}
}
