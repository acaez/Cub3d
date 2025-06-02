#include "../../inc/gnl.h"

static char	*ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*fill_line(int fd, char *left)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	b_read;
	char	*temp;

	if (!left)
		left = ft_strdup("");
	if (!left)
		return (NULL);
	while (!ft_strchr(left, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (ft_free(&left));
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		temp = ft_strjoin(left, buffer);
		if (!temp)
			return (ft_free(&left));
		free(left);
		left = temp;
	}
	return (left);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*save_remainder(char *buffer)
{
	char	*remainder;
	size_t	i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
		return (ft_free(&buffer));
	remainder = ft_strdup(buffer + i);
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char *stash[FD_MAX] = {NULL};
	char *line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);

	stash[fd] = fill_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);

	line = extract_line(stash[fd]);
	if (!line)
	{
		ft_free(&stash[fd]);
		return (NULL);
	}

	stash[fd] = save_remainder(stash[fd]);
	return (line);
}