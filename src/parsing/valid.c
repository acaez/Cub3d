/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:39:16 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 12:58:03 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
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
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr(" 01NSEW", map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_config(t_config *cfg, char **err)
{
	if (!file_exists(cfg->no_path)
		|| !file_exists(cfg->so_path)
		|| !file_exists(cfg->we_path)
		|| !file_exists(cfg->ea_path))
		return (*err = ft_strdup(ERR_TEXTURE_MISSING_FILE), false);
	if (!cfg->no_path || !cfg->so_path
		|| !cfg->we_path || !cfg->ea_path)
		return (*err = ft_strdup(ERR_TEXTURE_PATHS), false);
	if (cfg->floor_color == -1 || cfg->sky_color == -1)
		return (*err = ft_strdup(ERR_COLOR_MISSING), false);
	if (cfg->floor_color == cfg->sky_color)
		return (*err = ft_strdup(ERR_COLOR_IDENTICAL), false);
	if (!cfg->map || cfg->map_width <= 2 || cfg->map_height <= 2)
		return (*err = ft_strdup(ERR_MAP_INVALID_DIM), false);
	return (true);
}

bool	validate_map(char **map, char **err)
{
	if (!map_contains_only_valid_chars(map))
	{
		*err = ft_strdup(ERR_MAP_INVALID_CHARS);
		return (false);
	}
	if (!check_player_count(map))
	{
		*err = ft_strdup(ERR_PLAYER_COUNT);
		return (false);
	}
	if (!validate_closed_map(map))
	{
		*err = ft_strdup(ERR_MAP_NOT_CLOSED);
		return (false);
	}
	return (true);
}
