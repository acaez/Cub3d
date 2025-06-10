/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:05:44 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/10 17:05:46 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_game(t_game *game);
void	init_config(t_config *cfg);
void	init_player_from_map(t_game *game);
static	init_player(t_player *p);

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		exit_with_error(game, "Error: mlx_init() failed");
	game->map = game->config->map;
	if (game->map == NULL)
		exit_with_error(game, "Error: Failed to load the map");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		exit_with_error(game, "Error: mlx_new_window() failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img == NULL)
		exit_with_error(game, "Error: mlx_new_image() failed");
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (game->data == NULL)
		exit_with_error(game, "Error: mlx_get_data_addr() failed");
}


static    init_player(t_player *p)
{
    p->speed      = 5.0f;
    p->rot_speed  = 0.05f;
    p->key_up     = false;
    p->key_down   = false;
    p->key_left   = false;
    p->key_right  = false;
    p->rot_left   = false;
    p->rot_right  = false;
}

void	init_config(t_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	cfg->map = NULL;
	cfg->map_width = -1;
	cfg->map_height = -1;
}

void	init_player_from_map(t_game *game)
{
	int		y = 0;
	int		x;
	char	dir;

	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			dir = game->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				game->player.x = (x + 0.5f) * BLOCK;
				game->player.y = (y + 0.5f) * BLOCK;
				if (dir == 'N')
					game->player.angle = PI / 2;
				else if (dir == 'S')
					game->player.angle = 3 * PI / 2;
				else if (dir == 'E')
					game->player.angle = 0;
				else if (dir == 'W')
					game->player.angle = PI;
				game->map[y][x] = '0';
				init_player(&game->player);
				return ;
			}
			x++;
		}
		y++;
	}
	exit_with_error(game, "No player start position in map");
}

