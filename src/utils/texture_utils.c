#include "../../inc/cub3D.h"

int	get_wall_direction(float ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	if (ray_angle >= 0 && ray_angle < PI / 2)
		return (0);
	else if (ray_angle >= PI / 2 && ray_angle < PI)
		return (1);
	else if (ray_angle >= PI && ray_angle < 3 * PI / 2)
		return (2);
	else
		return (3);
}

void	calculate_vertical_wall(t_game *game, t_ray *ray, t_ray_vars *vars)
{
	ray->distance = (vars->map_x - game->player.x / BLOCK
			+ (1 - vars->step_x) / 2) / vars->dx;
	ray->hit_x = game->player.x + ray->distance * vars->dx * BLOCK;
	ray->hit_y = game->player.y + ray->distance * vars->dy * BLOCK;
	ray->wall_hit_x = (ray->hit_y / BLOCK) - floor(ray->hit_y / BLOCK);
	if (vars->step_x > 0)
		ray->wall_direction = 0;
	else
		ray->wall_direction = 2;
}

void	calculate_horizontal_wall(t_game *game, t_ray *ray, t_ray_vars *vars)
{
	ray->distance = (vars->map_y - game->player.y / BLOCK
			+ (1 - vars->step_y) / 2) / vars->dy;
	ray->hit_x = game->player.x + ray->distance * vars->dx * BLOCK;
	ray->hit_y = game->player.y + ray->distance * vars->dy * BLOCK;
	ray->wall_hit_x = (ray->hit_x / BLOCK) - floor(ray->hit_x / BLOCK);
	if (vars->step_y > 0)
		ray->wall_direction = 1;
	else
		ray->wall_direction = 3;
}

t_texture	*get_wall_texture(t_game *game, int direction)
{
	static t_texture	textures[4];
	static bool			loaded = false;

	if (!loaded)
{
		textures[0].img = mlx_xpm_file_to_image(game->mlx,
				game->config.ea_path, &textures[0].width, &textures[0].height);
		textures[1].img = mlx_xpm_file_to_image(game->mlx,
				game->config.so_path, &textures[1].width, &textures[1].height);
		textures[2].img = mlx_xpm_file_to_image(game->mlx,
				game->config.we_path, &textures[2].width, &textures[2].height);
		textures[3].img = mlx_xpm_file_to_image(game->mlx,
				game->config.no_path, &textures[3].width, &textures[3].height);
		textures[0].data = mlx_get_data_addr(textures[0].img,
				&textures[0].bpp, &textures[0].size_line, &textures[0].endian);
		textures[1].data = mlx_get_data_addr(textures[1].img,
				&textures[1].bpp, &textures[1].size_line, &textures[1].endian);
		textures[2].data = mlx_get_data_addr(textures[2].img,
				&textures[2].bpp, &textures[2].size_line, &textures[2].endian);
		textures[3].data = mlx_get_data_addr(textures[3].img,
				&textures[3].bpp, &textures[3].size_line, &textures[3].endian);
		loaded = true;
	}
	return (&textures[direction]);
}


