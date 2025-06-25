#include "../../inc/cub3D.h"

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	calculate_step_and_side_dist(t_game *game, t_ray_vars *vars)
{
	if (vars->dx < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (game->player.x / BLOCK - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - game->player.x / BLOCK)
			* vars->delta_dist_x;
	}
}

void	calculate_step_and_side_dist_y(t_game *game, t_ray_vars *vars)
{
	if (vars->dy < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (game->player.y / BLOCK - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - game->player.y / BLOCK)
			* vars->delta_dist_y;
	}
}

int	check_wall_hit(t_game *game, t_ray_vars *vars)
{
	if (vars->map_x < 0 || vars->map_y < 0
		|| vars->map_x >= game->config.map_width
		|| vars->map_y >= game->config.map_height
		|| game->config.map[vars->map_y][vars->map_x] == '1')
		return (1);
	return (0);
}

void	perform_dda_step(t_ray_vars *vars)
{
	if (vars->side_dist_x < vars->side_dist_y)
	{
		vars->side_dist_x += vars->delta_dist_x;
		vars->map_x += vars->step_x;
		vars->side = 0;
	}
	else
	{
		vars->side_dist_y += vars->delta_dist_y;
		vars->map_y += vars->step_y;
		vars->side = 1;
	}
}
