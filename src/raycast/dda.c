#include "../../inc/cub3D.h"

void	dda_setup(t_game *game, float ray_dir_x, float ray_dir_y, int map_x,
		int map_y, float *side_dist, float *delta_dist)
{
	if (ray_dir_x == 0)
		delta_dist[0] = 1e30;
	else
		delta_dist[0] = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist[1] = 1e30;
	else
		delta_dist[1] = fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		side_dist[0] = (game->player.x / BLOCK - map_x) * delta_dist[0];
		side_dist[2] = -1;
	}
	else
	{
		side_dist[0] = (map_x + 1.0 - game->player.x / BLOCK) * delta_dist[0];
		side_dist[2] = 1;
	}
	if (ray_dir_y < 0)
	{
		side_dist[1] = (game->player.y / BLOCK - map_y) * delta_dist[1];
		side_dist[3] = -1;
	}
	else
	{
		side_dist[1] = (map_y + 1.0 - game->player.y / BLOCK) * delta_dist[1];
		side_dist[3] = 1;
	}
}

void	perform_dda(t_game *game, float *side_dist, float *delta_dist,
		int *map_pos, int *hit_info)
{
	int hit;
	int side;
	int map_x;
	int map_y;

	map_x = map_pos[0];
	map_y = map_pos[1];
	hit = 0;
	while (!hit)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += delta_dist[0];
			map_x += (int)side_dist[2];
			side = 0;
		}
		else
		{
			side_dist[1] += delta_dist[1];
			map_y += (int)side_dist[3];
			side = 1;
		}
		if (map_x < 0 || map_y < 0 || map_y >= game->config.map_height
			|| map_x >= (int)ft_strlen(game->map[map_y])
			|| game->map[map_y][map_x] == '1')
			hit = 1;
	}
	hit_info[0] = map_x;
	hit_info[1] = map_y;
	hit_info[2] = side;
	hit_info[3] = (side_dist[side * 2 + 2] > 0) ? 1 : 0;
}