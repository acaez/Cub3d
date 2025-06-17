/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils 2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:14:54 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 15:12:19 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	copy_normalized_spaces(const char *src, char *dst)
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

char	*remove_trailing_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
