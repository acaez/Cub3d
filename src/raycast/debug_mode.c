#include "../../inc/cub3D.h"

static void	init_ray_vars(t_game *game, t_ray_vars *vars, float ray_angle)
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

static void	perform_debug_ray_casting(t_game *game, t_ray_vars *vars,
			t_ray *ray)
{
	calculate_step_and_side_dist(game, vars);
	calculate_step_and_side_dist_y(game, vars);
	while (vars->hit == 0)
	{
		perform_dda_step(vars);
		if (check_wall_hit(game, vars))
			vars->hit = 1;
	}
	if (vars->side == 0)
		calculate_vertical_wall(game, ray, vars);
	else
		calculate_horizontal_wall(game, ray, vars);
}

static void	draw_debug_full_map(t_game *game)
{
	t_debug_map	dm;
	int			x;
	int			y;

	dm.scale = calculate_debug_scale(game, &dm.offset_x, &dm.offset_y);
	draw_debug_background(game);
	y = 0;
	while (y < game->config.map_height)
	{
		x = 0;
		while (x < game->config.map_width && game->config.map[y][x])
		{
			draw_debug_cell(game, x, y, &dm);
			x++;
		}
		y++;
	}
	draw_debug_player(game, &dm);
}

static void	draw_debug_rays(t_game *game)
{
	t_debug_map	dm;
	int			x;
	float		ray_angle;
	float		angle_step;
	t_ray		ray;
	t_ray_vars	vars;

	dm.scale = calculate_debug_scale(game, &dm.offset_x, &dm.offset_y);
	x = 0;
	angle_step = (60 * PI / 180) / WIDTH;
	while (x < WIDTH)
	{
		ray_angle = game->player.angle - (30 * PI / 180) + x * angle_step;
		ray_angle = normalize_angle(ray_angle);
		init_ray_vars(game, &vars, ray_angle);
		perform_debug_ray_casting(game, &vars, &ray);
		draw_debug_impact(game, ray.hit_x, ray.hit_y, &dm);
		x += 4;
	}
}

static void	draw_debug_player_direction(t_game *game)
{
	t_debug_map	dm;
	int			player_screen_x;
	int			player_screen_y;
	int			end_x;
	int			end_y;
	int			steps;
	int			i;
	int			line_x;
	int			line_y;
	float		dx;
	float		dy;

	dm.scale = calculate_debug_scale(game, &dm.offset_x, &dm.offset_y);
	player_screen_x = dm.offset_x + (int)(game->player.x / BLOCK * dm.scale);
	player_screen_y = dm.offset_y + (int)(game->player.y / BLOCK * dm.scale);
	end_x = player_screen_x + (int)(cos(game->player.angle) * dm.scale);
	end_y = player_screen_y + (int)(sin(game->player.angle) * dm.scale);
	dx = end_x - player_screen_x;
	dy = end_y - player_screen_y;
	steps = (int)sqrt(dx * dx + dy * dy);
	if (steps > 0)
	{
		dx /= steps;
		dy /= steps;
		i = 0;
		while (i < steps)
		{
			line_x = player_screen_x + (int)(i * dx);
			line_y = player_screen_y + (int)(i * dy);
			if (line_x >= 0 && line_x < WIDTH && line_y >= 0
				&& line_y < HEIGHT)
				put_pixel(game, line_x, line_y, 0x00FF00);
			i++;
		}
	}
}

void	debug_mode(t_game *game)
{
	if (!game || !game->debug_mode)
		return;
	draw_debug_full_map(game);
	draw_debug_player_direction(game);
	draw_debug_rays(game);
}


