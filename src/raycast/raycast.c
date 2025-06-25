#include "../../inc/cub3D.h"

static void	init_ray_params(t_game *game, float ray_angle, float *params)
{
	params[0] = game->player.x;
	params[1] = game->player.y;
	params[2] = cos(ray_angle);
	params[3] = sin(ray_angle);
}

static float	cal_dist(float start_x, float start_y, float end_x, float end_y)
{
	return (sqrt((end_x - start_x) * (end_x - start_x)
			+ (end_y - start_y) * (end_y - start_y)));
}

static void	ray_hit(t_ray *ray, float ray_angle, float prev_x, float prev_y)
{
	ray->wall_direction = get_wall_direction(ray_angle);
	if (ray->wall_direction == 0 || ray->wall_direction == 2)
		ray->wall_hit_x = fmod(prev_y, BLOCK) / BLOCK;
	else
		ray->wall_hit_x = fmod(prev_x, BLOCK) / BLOCK;
}

static float	cast_ray(t_game *game, float ray_angle, t_ray *ray)
{
	float	params[4];
	float	distance;
	float	prev_x;
	float	prev_y;

	init_ray_params(game, ray_angle, params);
	distance = 0;
	while (!hit_wall(game, (int)params[0], (int)params[1]))
	{
		prev_x = params[0];
		prev_y = params[1];
		params[0] += params[2];
		params[1] += params[3];
		distance = cal_dist(game->player.x, game->player.y,
				params[0], params[1]);
		if (distance > 1000)
			break ;
	}
	ray->hit_x = params[0];
	ray->hit_y = params[1];
	ray_hit(ray, ray_angle, prev_x, prev_y);
	return (distance);
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
		draw_wall_column(game, x, &ray, distance);
		x++;
	}
}
