/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:49:57 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/10 16:53:02 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

bool    is_inside_map(char **map, int y, int x);
bool    is_open_char(char c);
bool	line_has_only_valid(char *s);

bool is_inside_map(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return false;
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return false;
	return true;
}

bool is_open_char(char c)
{
	return ft_strchr("0NSEW", c) != NULL;
}

bool    line_has_only_valid(char *s)
{
	while (*s)
	{
		if (!ft_strchr(" 01NSEW", *s))
			return (false);
		s++;
	}
	return (true);
}