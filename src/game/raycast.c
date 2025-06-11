#include "../inc/cub3D.h"

static void	draw_ceiling_floor(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = game->config.ceiling_color ? game->config.ceiling_color : 0x87CEEB;
	floor_color = game->config.floor_color ? game->config.floor_color : 0x8B4513;
	
	// Draw ceiling
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	
	// Draw floor
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

static int	get_wall_color(float ray_x, float ray_y)
{
	int	wall_color;

	// Check if hitting vertical wall (East/West facing)
	if (fabs(ray_x - (int)(ray_x / BLOCK) * BLOCK) < 0.1 || 
		fabs(ray_x - ((int)(ray_x / BLOCK) + 1) * BLOCK) < 0.1)
	{
		// Determine if East or West facing based on ray_y
		if ((int)ray_y % 2 == 0)
			wall_color = 0xAA0000; // Darker red for East walls
		else
			wall_color = 0x880000; // Even darker red for West walls
	}
	else // Hitting horizontal wall (North/South facing)
	{
		// Determine if North or South facing based on ray_y
		if (fabs(ray_y - (int)(ray_y / BLOCK) * BLOCK) < 0.1)
			wall_color = 0xFF0000; // Bright red for North walls
		else
			wall_color = 0xDD0000; // Less bright red for South walls
	}
	return (wall_color);
}

static void	draw_wall_column(t_game *game, int x, float corrected_dist, float ray_x, float ray_y)
{
	int	wall_height;
	int	start_y;
	int	end_y;
	int	wall_color;
	int	y;

	// Calculate wall height based on distance
	wall_height = (int)(HEIGHT / corrected_dist * BLOCK / 2);
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	
	// Calculate starting and ending Y coordinates
	start_y = (HEIGHT / 2) - (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	
	// Get wall color based on direction
	wall_color = get_wall_color(ray_x, ray_y);
	
	// Draw the wall column
	y = start_y;
	while (y <= end_y)
	{
		put_pixel(game, x, y, wall_color);
		y++;
	}
}

static void	cast_rays(t_game *game)
{
	int		x;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	step_size;
	bool	hit_wall;
	char	**map;

	map = game->map;
	x = 0;
	step_size = 0.1;
	
	while (x < WIDTH)
	{
		ray_angle = game->player.angle - (PI / 6) + ((float)x / WIDTH) * (PI / 3);
		ray_x = game->player.x;
		ray_y = game->player.y;
		dist = 0;
		hit_wall = false;
		
		// For debug mode, only draw every 50th ray to reduce visual clutter
		bool draw_debug_ray = (game->debug_mode && x % 50 == 0);
		
		while (!hit_wall && dist < 20)
		{
			dist += step_size;
			ray_x = game->player.x + cos(ray_angle) * dist;
			ray_y = game->player.y + sin(ray_angle) * dist;
			
			// Draw the ray path in debug mode
			if (draw_debug_ray && game->debug_mode)
			{
				put_pixel(game, ray_x, ray_y, 0x00FF00);
			}
			
			// Check if ray hits a wall
			int map_x = (int)(ray_x / BLOCK);
			int map_y = (int)(ray_y / BLOCK);
			
			if (map_x < 0 || map_y < 0 || map_y >= 11 || map_x >= (int)ft_strlen(map[0]) || 
				map[map_y][map_x] == '1')
			{
				hit_wall = true;
				float corrected_dist = dist * cos(ray_angle - game->player.angle);
				draw_wall_column(game, x, corrected_dist, ray_x, ray_y);
				if (draw_debug_ray && game->debug_mode)
				{
					put_pixel(game, ray_x, ray_y, 0xFF0000);
					put_pixel(game, ray_x+1, ray_y, 0xFF0000);
					put_pixel(game, ray_x, ray_y+1, 0xFF0000);
					put_pixel(game, ray_x+1, ray_y+1, 0xFF0000);
				}
			}
		}
		x++;
	}
}

void	draw_scene(t_game *game)
{
	draw_ceiling_floor(game);
	cast_rays(game);
	
	// Draw minimap if debug mode is enabled
	if (game->debug_mode)
	{
		draw_map(game);
		draw_minimap(game);
		draw_filled_square(game, game->player.x - 5, game->player.y - 5, 10, 0x00FF00);
		int i = 0;
		while (i < 20)
		{
			float px = game->player.x + cos(game->player.angle) * i;
			float py = game->player.y + sin(game->player.angle) * i;
			put_pixel(game, px, py, 0xFFFF00);
			i++;
		}
	}
}

int	game_loop(t_game *game)
{
	move_player(&game->player);
	clear_image(game);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

