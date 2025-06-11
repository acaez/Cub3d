#include "../../inc/cub3D.h"

void	free_map(char **map)
{
	int	i;
	
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
		free(cfg->map);
}

static void	exit_game(t_game *game, int exit_code)
{
	if (game)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
#ifdef LINUX
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

void	exit_error(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit_game(game, 1);
}

int	close_window(t_game *game)
{
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	exit_game(game, 0);
	return (0);
}

