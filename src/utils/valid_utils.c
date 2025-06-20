/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:07:13 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 12:33:32 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

bool file_exists(const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

bool	is_inside_map(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (false);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (false);
	return (true);
}

bool	is_open_char(char c)
{
	return (ft_strchr("0NSEW", c) != NULL);
}
