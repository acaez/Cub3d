#include "../../inc/cub3D.h"

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

bool	hit_wall(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (true);
	map_x = x / BLOCK;
	map_y = y / BLOCK;
	if (map_x >= game->config.map_width || map_y >= game->config.map_height)
		return (true);
	if (game->config.map[map_y][map_x] == '1')
		return (true);
	return (false);
}

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
