#include "../../inc/cub3D.h"

bool is_inside_map(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return false;
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return false;
	return true;
}

bool is_open_char(char c)
{
	return ft_strchr("0NSEW", c) != NULL;
}

bool    line_has_only_valid(char *s)
{
	while (*s)
	{
		if (!ft_strchr(" 01NSEW", *s))
			return (false);
		s++;
	}
	return (true);
}
