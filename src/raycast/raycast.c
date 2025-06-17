/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 11:00:00 by matsauva         ###   ########.fr       */
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

void draw_square(t_game *game, int x, int y, int size, int color)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

void draw_debug(t_game *game, t_player *player, float start_x)
{
	float cos_angle;
    float sin_angle;
	float ray_x;
    float ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
    ray_y = player->y;
	while(!check_collision(&game->config, ray_x, ray_y))
    {
        if(game->debug_mode)
            put_pixel(game, ray_x, ray_y, 0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
}
void draw_line(t_game *game, t_player *player, float start_x, int i)
{
	float	ray_x;
    float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

    if(!game->debug_mode)
    {
        dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
        height = (BLOCK / dist) * (WIDTH / 2);
        start_y = (HEIGHT - height) / 2;
        end = start_y + height;
        while(start_y < end)
        {
            put_pixel(i, start_y, 255, game);
            start_y++;
        }
    }
}

int raycast(t_game *game)
{
    t_player	*player;
	float       fraction;
	float       start_x;
	int         i;
	
	player = &game->player;
	if(game->debug_mode)
    {
        draw_square(game, 0, 0, WIDTH, 0x000000);
        draw_map(game);
    }
    fraction = PI / 3 / WIDTH;
    start_x = player->angle - PI / 6;
    i = 0;
    while(i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    return 0;
}
