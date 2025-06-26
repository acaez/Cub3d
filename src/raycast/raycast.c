#include "../../inc/cub3D.h"

static void	init_ray(t_game *game, float ray_angle, t_ray_vars *vars)
{
	vars->dx = cos(ray_angle);
	vars->dy = sin(ray_angle);
	vars->map_x = (int)(game->player.x / BLOCK);
	vars->map_y = (int)(game->player.y / BLOCK);
	if (vars->dx == 0)
		vars->delta_dist_x = 1e30;
	else
		vars->delta_dist_x = fabs(1.0 / vars->dx);
	if (vars->dy == 0)
		vars->delta_dist_y = 1e30;
	else
		vars->delta_dist_y = fabs(1.0 / vars->dy);
	vars->hit = 0;
}

static void	perform_dda(t_game *game, t_ray_vars *vars)
{
	while (vars->hit == 0)
	{
		perform_dda_step(vars);
		if (check_wall_hit(game, vars))
			vars->hit = 1;
	}
}

static void	calculate_ray_distance_and_position(t_game *game, t_ray *ray,
											t_ray_vars *vars)
{
	if (vars->side == 0)
		calculate_vertical_wall(game, ray, vars);
	else
		calculate_horizontal_wall(game, ray, vars);
	if (ray->wall_direction == 2 || ray->wall_direction == 3)
		ray->wall_hit_x = 1.0 - ray->wall_hit_x;
	ray->distance *= BLOCK;
}

static float	cast_ray(t_game *game, float ray_angle, t_ray *ray)
{
	t_ray_vars	vars;

	init_ray(game, ray_angle, &vars);
	calculate_step_and_side_dist(game, &vars);
	calculate_step_and_side_dist_y(game, &vars);
	perform_dda(game, &vars);
	calculate_ray_distance_and_position(game, ray, &vars);
	return (ray->distance);
}

void	raycast(t_game *game)
{
	int		x;
	float	ray_angle;
	float	distance;
	float	angle_step;
	t_ray	ray;

	x = 0;
	angle_step = (60 * PI / 180) / WIDTH;
	while (x < WIDTH)
	{
		ray_angle = game->player.angle - (30 * PI / 180) + x * angle_step;
		ray_angle = normalize_angle(ray_angle);
		distance = cast_ray(game, ray_angle, &ray);
		draw_texture(game, x, &ray, distance);
		x++;
	}
}
