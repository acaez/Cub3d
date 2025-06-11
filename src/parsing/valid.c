#include "../../inc/cub3D.h"

static bool	validate_closed_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_open_char(map[y][x]) &&
				(!is_inside_map(map, y - 1, x) || map[y - 1][x] == ' ' ||
				 !is_inside_map(map, y + 1, x) || map[y + 1][x] == ' ' ||
				 !is_inside_map(map, y, x - 1) || map[y][x - 1] == ' ' ||
				 !is_inside_map(map, y, x + 1) || map[y][x + 1] == ' '))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	check_player_count(char **map)
{
	int	y = 0;
	int	x;
	int	count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count == 1);
}

static bool	map_contains_only_valid_chars(char **map)
{
	int	y = 0;

	while (map[y])
	{
		if (!line_has_only_valid(map[y]))
			return (false);
		y++;
	}
	return (true);
}

bool    validate_map(char **map)
{
    if (!map_contains_only_valid_chars(map))
    {
        printf("Map validation failed: contains invalid characters\n");
        return (false);
    }
    if (!check_player_count(map))
    {
        printf("Map validation failed: player count issue\n");
        return (false);
    }
    if (!validate_closed_map(map))
    {
        printf("Map validation failed: map is not properly closed\n");
        return (false);
    }
    return (true);
}
