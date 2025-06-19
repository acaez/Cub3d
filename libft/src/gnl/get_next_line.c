/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:34:17 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/19 16:49:18 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gnl.h"

static char	*g_stash[FD_MAX] = {NULL};

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
	char	*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0
		|| BUFFER_SIZE >= INT_MAX)
		return (NULL);
	g_stash[fd] = fill_line(fd, g_stash[fd]);
	if (!g_stash[fd])
		return (NULL);
	line = extract_line(g_stash[fd]);
	if (!line)
	{
		ft_free(&g_stash[fd]);
		return (NULL);
	}
	g_stash[fd] = save_remainder(g_stash[fd]);
	return (line);
}

void	gnl_clear(int fd)
{
	if (fd < 0 || fd >= FD_MAX)
		return ;
	ft_free(&g_stash[fd]);
}
