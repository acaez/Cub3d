/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:44:21 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/16 15:39:46 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	game_loop(t_game *game)
{
	move_player(&game->player);
	printf("Player at: %.2f, %.2f\n", game->player.x, game->player.y);
	clear_image(game);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
