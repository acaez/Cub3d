/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:25:36 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/10 17:02:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	exit_with_error(t_game *game, char *msg);
void	exit_game(t_game *game, int exit_code);
int		exit_game_hook(t_game *game);
void	free_config(t_config *cfg);
void	free_map(char **map);

void	exit_with_error(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit_game(game, 1);  // Error exit
}

void	exit_game(t_game *game, int exit_code)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
#ifdef __linux__
		if (game->mlx)
			mlx_destroy_display(game->mlx);
#endif
		if (game->mlx)
			free(game->mlx);
		if (game->map)
			free_map(game->map);
	}
	exit(exit_code);
}

int	exit_game_hook(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

void	free_config(t_config *cfg)
{
	if (cfg->no_path)
		free(cfg->no_path);
	if (cfg->so_path)
		free(cfg->so_path);
	if (cfg->we_path)
		free(cfg->we_path);
	if (cfg->ea_path)
		free(cfg->ea_path);
	if (cfg->map)
		free_map(cfg->map);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

