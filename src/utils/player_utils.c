#include "../../inc/cub3D.h"

static int	is_blocked_at(t_config *config, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / BLOCK);
	map_y = (int)(y / BLOCK);
	if (map_x < 0 || map_y < 0)
		return (1);
	if (!is_inside_map(config->map, map_y, map_x))
		return (1);
	if (!is_open_char(config->map[map_y][map_x]))
		return (1);
	return (0);
}

int	check_collision(t_config *config, float x, float y)
{
	float	margin;

	if (!config || !config->map)
		return (1);
	margin = BLOCK * 0.1;
	if (is_blocked_at(config, x, y))
		return (1);
	if (is_blocked_at(config, x + margin, y))
		return (1);
	if (is_blocked_at(config, x - margin, y))
		return (1);
	if (is_blocked_at(config, x, y + margin))
		return (1);
	if (is_blocked_at(config, x, y - margin))
		return (1);
	return (0);
}
