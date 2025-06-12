#include "../../inc/cub3D.h"

#include <fcntl.h>   // pour open()
#include <stdio.h>   // pour printf()
#include <unistd.h>  // pour close()

////////////////
char *normalize_spaces(char *str)
{
	char	*dst;
	int		i;
	int		j;
	bool	in_space;

	i = 0;
	j = 0;
	in_space = false;
	dst = malloc(ft_strlen(str) + 1);
	if (!dst)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (!in_space)
				dst[j++] = ' ';
			in_space = true;
		}
		else
		{
			dst[j++] = str[i];
			in_space = false;
		}
		i++;
	}
	dst[j] = '\0';
	return (ft_strtrim_free(dst, " "));
}

bool	is_empty_line(const char *line)
{
	const char	*p = line;

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
	size_t	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

///////////////////

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
	if (!ft_strcmp(tokens[0], "NO") || !ft_strcmp(tokens[0], "SO") ||
		!ft_strcmp(tokens[0], "WE") || !ft_strcmp(tokens[0], "EA"))
		success = set_texture(cfg, tokens[0], tokens[1]);
	else if (!ft_strcmp(tokens[0], "F"))
		success = parse_color(tokens[1], &cfg->floor_color);
	else if (!ft_strcmp(tokens[0], "C"))
		success = parse_color(tokens[1], &cfg->ceiling_color);

	free_map(tokens);
	return (success);
}

static bool	parse_map(t_config *cfg, int fd, char *line)
{
	int		map_capacity;
	int		map_size;

	map_capacity = 16;
	map_size = 0;
	cfg->map = ft_calloc(map_capacity + 1, sizeof(char *));
	if (!cfg->map)
	{
		free(line);
		return (false);
	}
	line = remove_trailing_newline(line);
	cfg->map[map_size++] = line;
	while ((line = get_next_line(fd)))
	{
		printf("Read line: %s", line);
		if (map_size >= map_capacity)
		{
			map_capacity *= 2;
			char **new_map = ft_realloc_tab(cfg->map, map_capacity);
			if (!new_map)
			{
				free(line);
				free_map(cfg->map);
				return (false);
			}
			cfg->map = new_map;
		}
		line = remove_trailing_newline(line);
		cfg->map[map_size++] = line;
	}
	cfg->map[map_size] = NULL;
	if (line)
		free(line);
	// To do padding
	cfg->map_height = map_size;
	cfg->map_width = get_map_width(cfg->map);
	return (true);
}

bool	parse_cub_file(t_config *cfg, char *path)
{
	int		fd;
	char	*line;

	printf("Trying to open file: %s\n", path);
	cfg->map = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file: %s\n", path);
		perror("open");
		return (false);
	}
	while ((line = get_next_line(fd)))
	{
		printf("Read line: %s", line);
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (is_map_line(line)) // first line of the map detected (first line with 1 after trailing space)
		{
			if (!parse_map(cfg, fd, line)) // parse the entire map from this point
			{
				printf("Failed to parse map.\n");
				close(fd);
				return (false);
			}
			// After the map: only allow empty lines, anything else is an error
			while ((line = get_next_line(fd)))
			{
				if (!is_empty_line(line))
				{
					printf("Unexpected content after map: \"%s\"\n", line);
					free(line);
					close(fd);
					return (false);
				}
				free(line);
			}
			break ; // parsing complete
		}
		if (!parse_line(cfg, line)) // handle config lines
		{
			printf("Failed to parse config line: %s\n", line);
			free(line);
			close(fd);
			return (false);
		}
		free(line);
	}
	close(fd);
	printf("File parsed successfully.\n");
	return (true);
}
