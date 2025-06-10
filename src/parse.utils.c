/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:43:11 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/10 16:45:39 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool    is_map_line(const char *line);
int     parse_color(char *line);
void    set_texture(t_config *cfg, char *id, char *path);

char	*ft_strtrim_free(char *str, const char *set)
{
	char *trimmed = ft_strtrim(str, set);
	free(str);
	return (trimmed);
}

char	**ft_realloc_tab(char **old, int new_size)
{
	char	**new_tab;
	int		i = 0;

	new_tab = ft_calloc(new_size + 1, sizeof(char *));
	while (old[i])
	{
		new_tab[i] = old[i];
		i++;
	}
	free(old);
	return (new_tab);
}

bool    is_map_line(const char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == ' ' ||
			*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			return (true);
		line++;
	}
	return (false);
}

int parse_color(char *line)
{
	char	**parts;
	int		r, g, b, color;

	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (-1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	color = (r << 16) | (g << 8) | b;
	free_map(parts);
	return (color);
}

void    set_texture(t_config *cfg, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		cfg->no_path = ft_strdup(path);
	else if (ft_strncmp(id, "SO", 2) == 0)
		cfg->so_path = ft_strdup(path);
	else if (ft_strncmp(id, "WE", 2) == 0)
		cfg->we_path = ft_strdup(path);
	else if (ft_strncmp(id, "EA", 2) == 0)
		cfg->ea_path = ft_strdup(path);
}