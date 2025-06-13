/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:11:15 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/13 13:12:21 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	print_config(const t_config *cfg)
{
	if (!cfg)
		return ;
	printf("Config debug dump:\n");
	printf("NO: %s\n", cfg->no_path);
	printf("SO: %s\n", cfg->so_path);
	printf("WE: %s\n", cfg->we_path);
	printf("EA: %s\n", cfg->ea_path);
	printf("Floor:   %06X\n", cfg->floor_color);
	printf("Ceiling: %06X\n", cfg->ceiling_color);
	printf("Map size: %d x %d\n", cfg->map_width, cfg->map_height);
}

void	print_map(char **map)
{
	int	y;
	int	x;

	printf("Map:\n");
	if (!map)
	{
		printf("(null)\n");
		return ;
	}
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				putchar('*');
			else
				putchar(map[y][x]);
			++x;
		}
		putchar('\n');
		++y;
	}
}
