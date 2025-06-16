/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:59:20 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 16:15:24 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	setup_dir(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player.angle = PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = PI;
}

void	setup_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->config.map[y])
	{
		x = 0;
		while (game->config.map[y][x])
		{
			if (ft_strchr("NSEW", game->config.map[y][x]))
			{
				game->player.x = x * BLOCK + BLOCK / 2;
				game->player.y = y * BLOCK + BLOCK / 2;
				setup_dir(game, game->config.map[y][x]);
				game->config.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
