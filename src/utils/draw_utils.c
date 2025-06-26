/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:44:21 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:21:44 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	size;
	int	color;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	size = 4;
	color = 0xFF0000;
	i = -size;
	while (i <= size)
	{
		put_pixel(game, cx + i, cy, color);
		i++;
	}
	i = -size;
	while (i <= size)
	{
		put_pixel(game, cx, cy + i, color);
		i++;
	}
}

void	draw_pause_overlay(t_game *game)
{
	int	rect_x;
	int	rect_y;
	int	i;
	int	j;

	rect_x = (WIDTH - PAUSE_RECT_W) / 2;
	rect_y = (HEIGHT - PAUSE_RECT_H) / 2;
	i = 0;
	while (i < PAUSE_RECT_H)
	{
		j = 0;
		while (j < PAUSE_RECT_W)
		{
			mlx_pixel_put(game->mlx, game->win, rect_x + j, rect_y + i,
				0x000000);
			j++;
		}
		i++;
	}
	mlx_string_put(game->mlx, game->win, PAUSE_TXT1_X, PAUSE_TXT1_Y,
		0xFFFFFF, PAUSE_MSG1);
	mlx_string_put(game->mlx, game->win, PAUSE_TXT2_X, PAUSE_TXT2_Y,
		0xFFFFFF, PAUSE_MSG2);
}

void	update_fps(t_game *game)
{
	clock_t	current_time;
	double	elapsed;

	game->frame_count++;
	current_time = clock();
	elapsed = ((double)(current_time - game->last_time)) / CLOCKS_PER_SEC;
	if (elapsed >= 1.0)
	{
		game->fps = (int)(game->frame_count / elapsed);
		game->frame_count = 0;
		game->last_time = current_time;
	}
}

void	draw_fps(t_game *game)
{
	char	*fps_str;
	char	*fps_num;

	if (!game->show_fps)
		return ;
	fps_num = ft_itoa(game->fps);
	if (!fps_num)
		return ;
	fps_str = ft_strjoin("FPS: ", fps_num);
	free(fps_num);
	if (!fps_str)
		return ;
	mlx_string_put(game->mlx, game->win, WIDTH - 80, 20, 0xFFFFFF, fps_str);
	free(fps_str);
}
