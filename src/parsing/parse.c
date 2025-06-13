/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:50 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 16:11:48 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	copy_normalized_spaces(const char *src, char *dst)
{
	int		i;
	int		j;
	bool	in_space;

	i = 0;
	j = 0;
	in_space = false;
	while (src[i])
	{
		if (src[i] == ' ' || src[i] == '\t')
		{
			if (!in_space)
				dst[j++] = ' ';
			in_space = true;
		}
		else
		{
			dst[j++] = src[i];
			in_space = false;
		}
		i++;
	}
	dst[j] = '\0';
}

char	*normalize_spaces(char *str)
{
	char	*dst;
	int		len;

	len = ft_strlen(str);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	copy_normalized_spaces(str, dst);
	return (ft_strtrim_free(dst, " "));
}

bool	is_empty_line(const char *line)
{
	const char	*p;

	p = line;
	if (!p)
		return (true);
	while (*p)
	{
		if (*p != ' ' && *p != '\t' && *p != '\n')
			return (false);
		p++;
	}
	return (true);
}

static char	*remove_trailing_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static bool	parse_line(t_config *cfg, char *line)
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
		success = parse_color(tokens[1], &cfg->ceiling_color);
	free_map(tokens);
	return (success);
}

static bool	add_line_to_map(t_config *cfg, char *line, int *sz, int *cap)
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

static bool	read_map_lines(t_config *cfg, int fd, char *line)
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

static bool	parse_map(t_config *cfg, int fd, char *line)
{
	if (!read_map_lines(cfg, fd, line))
		return (false);
	/* TODO: add padding if required                           */
	cfg->map_height = get_map_height(cfg->map);
	cfg->map_width = get_map_width(cfg->map);
	return (true);
}

static bool	handle_trailing_lines(int fd, char **err)
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
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
