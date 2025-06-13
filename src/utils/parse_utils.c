/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:14:54 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 13:15:13 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

char	*ft_strtrim_free(char *str, const char *set)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, set);
	free(str);
	return (trimmed);
}

char	**ft_realloc_tab(char **old, int new_size)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = ft_calloc(new_size + 1, sizeof(char *));
	while (old[i])
	{
		new_tab[i] = old[i];
		i++;
	}
	free(old);
	return (new_tab);
}

bool	is_map_line(char *line)
{
	const char	*p;

	if (!line)
		return (false);
	p = line;
	while (*p == ' ')
		p++;
	return (*p == '1');
}

bool	parse_color(char *line, int *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_map(parts);
		return (false);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_map(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	*color = (r << 16) | (g << 8) | b;
	return (true);
}

bool	set_texture(t_config *cfg, const char *id, const char *path)
{
	if (!id || !path)
		return (false);
	if (ft_strncmp(id, "NO", 3) == 0 && !cfg->no_path)
		cfg->no_path = ft_strdup(path);
	else if (ft_strncmp(id, "SO", 3) == 0 && !cfg->so_path)
		cfg->so_path = ft_strdup(path);
	else if (ft_strncmp(id, "WE", 3) == 0 && !cfg->we_path)
		cfg->we_path = ft_strdup(path);
	else if (ft_strncmp(id, "EA", 3) == 0 && !cfg->ea_path)
		cfg->ea_path = ft_strdup(path);
	else
		return (false);
	return (true);
}
