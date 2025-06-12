#include "../../inc/cub3D.h"

static int	get_wall_color(int side, int wall_dir)
{
	if (side == 0)
	{
		if (wall_dir == 1)
			return (0xAA0000);  /* East wall */
		return (0x880000);  /* West wall */
	}
	else
	{
		if (wall_dir == 1)
			return (0xFF0000);  /* North wall */
		return (0xDD0000);  /* South wall */
	}
}

static void	draw_wall_column(t_game *game, int x, float perp_wall_dist, 
						int side, int wall_dir)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	wall_color;
	int	y;

	line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	wall_color = get_wall_color(side, wall_dir);
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel(game, x, y, wall_color);
		y++;
	}
}

static void	draw_debug_ray(t_game *game, int x, int map_x, int map_y)
{
	int		i;
	float	px;
	float	py;
	float	ray_angle;

	if (!game->debug_mode || x % 50 != 0)
		return ;
	ray_angle = game->player.angle - (PI / 6) + ((float)x / WIDTH) * (PI / 3);
	i = 0;
	while (i < 20 * BLOCK)
	{
		px = game->player.x + cos(ray_angle) * i / 20.0;
		py = game->player.y + sin(ray_angle) * i / 20.0;
		if ((int)(px / BLOCK) == map_x && (int)(py / BLOCK) == map_y)
			put_pixel(game, px, py, 0xFF0000);
		else
			put_pixel(game, px, py, 0x00FF00);
		i++;
	}
}

void	raycast(t_game *game)
{
	int		x;
	int		map_pos[2];
	int		hit_info[4];
	float	camera_x;
	float	ray_dir[2];
	float	side_dist[4];
	float	delta_dist[2];
	float	perp_wall_dist;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (float)WIDTH - 1;
		ray_dir[0] = cos(game->player.angle) + sin(game->player.angle) * camera_x;
		ray_dir[1] = sin(game->player.angle) - cos(game->player.angle) * camera_x;
		map_pos[0] = (int)(game->player.x / BLOCK);
		map_pos[1] = (int)(game->player.y / BLOCK);
		dda_setup(game, ray_dir[0], ray_dir[1], map_pos[0], map_pos[1], 
				side_dist, delta_dist);
		perform_dda(game, side_dist, delta_dist, map_pos, hit_info);
		if (hit_info[2] == 0)
			perp_wall_dist = (hit_info[0] - game->player.x / BLOCK + 
							(1 - (int)side_dist[2]) / 2) / ray_dir[0];
		else
			perp_wall_dist = (hit_info[1] - game->player.y / BLOCK + 
							(1 - (int)side_dist[3]) / 2) / ray_dir[1];
		perp_wall_dist = perp_wall_dist * BLOCK;
		draw_wall_column(game, x, perp_wall_dist, hit_info[2], hit_info[3]);
		draw_debug_ray(game, x, hit_info[0], hit_info[1]);
		x++;
	}
}