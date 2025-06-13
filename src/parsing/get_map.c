/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:47:09 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 15:50:01 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

bool	pad_map_in_place(char **map, size_t max_len, char pad)
{
	size_t	len;
	int		y;
	char	*new_line;

	y = 0;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		if (len < max_len)
		{
			new_line = ft_calloc(max_len + 1, 1);
			if (!new_line)
				return (false);
			ft_memcpy(new_line, map[y], len);
			ft_memset(new_line + len, pad, max_len - len);
			free(map[y]);
			map[y] = new_line;
		}
		y++;
	}
	return (true);
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

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}
