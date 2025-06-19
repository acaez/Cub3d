/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:50 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 16:25:38 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static bool	parse_map(t_config *cfg, int fd, char *line)
{
	if (!read_map_lines(cfg, fd, line))
		return (false);
	cfg->map_height = get_map_height(cfg->map);
	cfg->map_width = get_map_width(cfg->map);
	return (true);
}

static bool	start_map_parsing(t_config *cfg, int fd, char *line, char **err)
{
	if (!parse_map(cfg, fd, line))
	{
		*err = ft_strdup("Failed to parse map.");
		return (false);
	}
	if (!handle_trailing_lines(fd, err))
		return (false);
	return (true);
}

static bool	handle_line(t_config *cfg, int fd, char *line, char **err)
{
	if (is_empty_line(line))
	{
		free(line);
		return (true);
	}
	if (is_map_line(line))
		return (start_map_parsing(cfg, fd, line, err));
	if (!parse_line(cfg, line))
	{
		*err = ft_strjoin("Failed to parse config line: ", line);
		free(line);
		return (false);
	}
	free(line);
	return (true);
}

static bool	parse_file_lines(t_config *cfg, int fd, char **err)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!handle_line(cfg, fd, line, err))
			return (false);
		line = get_next_line(fd);
	}
	return (true);
}

bool	parse_cub_file(t_config *cfg, char *path, char **err)
{
	int	fd;

	cfg->map = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*err = ft_strdup("Failed to open map file.");
		return (false);
	}
	if (!parse_file_lines(cfg, fd, err))
	{
		gnl_clear(fd);
		close(fd);
		return (false);
	}
	gnl_clear(fd);
	close(fd);
	return (true);
}
