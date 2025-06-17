/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils 3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:14:54 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 15:12:34 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

bool	parse_line(t_config *cfg, char *line)
{
	char	**tokens;
	bool	success;
	char	*clean;

	success = false;
	line = remove_trailing_newline(line);
	clean = normalize_spaces(line);
	tokens = ft_split(clean, ' ');
	free(clean);
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		free_map(tokens);
		return (false);
	}
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO")
		|| !ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
		success = set_texture(cfg, tokens[0], tokens[1]);
	else if (!ft_strcmp(tokens[0], "F"))
		success = parse_color(tokens[1], &cfg->floor_color);
	else if (!ft_strcmp(tokens[0], "C"))
		success = parse_color(tokens[1], &cfg->sky_color);
	free_map(tokens);
	return (success);
}

bool	add_line_to_map(t_config *cfg, char *line, int *sz, int *cap)
{
	char	**tmp;

	if (*sz >= *cap)
	{
		*cap *= 2;
		tmp = ft_realloc_tab(cfg->map, *cap);
		if (!tmp)
		{
			free(line);
			free_map(cfg->map);
			return (false);
		}
		cfg->map = tmp;
	}
	line = remove_trailing_newline(line);
	cfg->map[(*sz)++] = line;
	return (true);
}

bool	read_map_lines(t_config *cfg, int fd, char *line)
{
	int		cap;
	int		size;

	cap = 16;
	size = 0;
	cfg->map = ft_calloc(cap + 1, sizeof(char *));
	if (!cfg->map)
	{
		free(line);
		return (false);
	}
	if (!add_line_to_map(cfg, line, &size, &cap))
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		if (!add_line_to_map(cfg, line, &size, &cap))
			return (false);
		line = get_next_line(fd);
	}
	cfg->map[size] = NULL;
	return (true);
}

bool	handle_trailing_lines(int fd, char **err)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			*err = ft_strjoin("Unexpected content after map: ", line);
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
