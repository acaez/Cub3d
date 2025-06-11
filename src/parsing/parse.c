#include "../../inc/cub3D.h"

static bool	parse_line(t_config *cfg, char *line)
{
	char	**tokens;

	if (is_map_line(line))
		return (true);

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (false);
	if (ft_strncmp(tokens[0], "NO", 2) == 0 || ft_strncmp(tokens[0], "SO", 2) == 0 ||
		ft_strncmp(tokens[0], "WE", 2) == 0 || ft_strncmp(tokens[0], "EA", 2) == 0)
		set_texture(cfg, tokens[0], tokens[1]);
	else if (tokens[0][0] == 'F')
		cfg->floor_color = parse_color(tokens[1]);
	else if (tokens[0][0] == 'C')
		cfg->ceiling_color = parse_color(tokens[1]);
	else
		return (false);
	free_map(tokens);
	return (true);
}

static bool	parse_map(t_config *cfg, int fd, char *line)
{
	int		map_capacity = 16;
	int		map_size = 0;

	cfg->map = ft_calloc(map_capacity + 1, sizeof(char *));
	if (!cfg->map)
		return (false);
	while (line && is_map_line(line))
	{
		if (map_size >= map_capacity)
		{
			map_capacity *= 2;
			cfg->map = ft_realloc_tab(cfg->map, map_capacity);
			if (!cfg->map)
				return (false);
		}
		cfg->map[map_size++] = line;
		line = get_next_line(fd);
		if (line)
			line = ft_strtrim_free(line, "\n");
	}
	cfg->map[map_size] = NULL;
	if (line)
		free(line);
	return (true);
}

bool	parse_cub_file(t_config *cfg, char *path)
{
	int		fd;
	char	*line;

	cfg->map = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((line = get_next_line(fd)))
	{
		line = ft_strtrim_free(line, "\n");
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (is_map_line(line))
		{
			if (!parse_map(cfg, fd, line))
			{
				close(fd);
				return (false);
			}
			break ;
		}
		if (!parse_line(cfg, line))
		{
			free(line);
			close(fd);
			return (false);
		}
		free(line);
	}
	close(fd);
	return (true);
}
