/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:50:08 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 14:39:06 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_config(t_config *cfg)
{
	if (cfg->no_path)
		free(cfg->no_path);
	if (cfg->so_path)
		free(cfg->so_path);
	if (cfg->we_path)
		free(cfg->we_path);
	if (cfg->ea_path)
		free(cfg->ea_path);
	if (cfg->map)
	{
		free_map(cfg->map);
		cfg->map = NULL;
	}
}

void	free_trigo(t_trigo *trigo)
{
	if (trigo->cos_table)
		free(trigo->cos_table);
	if (trigo->sin_table)
		free(trigo->sin_table);
}
