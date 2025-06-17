/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:33 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		index = y * game->size_line + x * (game->bpp / 8);
		game->data[index] = color & 0xFF;
		game->data[index + 1] = (color >> 8) & 0xFF;
		game->data[index + 2] = (color >> 16) & 0xFF;
	}
}

t_ray_hit	calculate_distance(t_game *game, float start_x, float start_y, float angle)
{
	float		dx, dy;
	int			map_x, map_y;
	float		delta_dist_x, delta_dist_y;
	int			step_x, step_y;
	float		side_dist_x, side_dist_y;
	int			hit, side;
	t_ray_hit	result;
	
	// Utiliser les tables trigo précalculées si disponibles
	if (game->trigo.cos_table)
		get_trigo_value(&game->trigo, angle, &dx, &dy);
	else
	{
		dx = cosf(angle);
		dy = sinf(angle);
	}
	
	// Position actuelle en coordonnées de grille
	map_x = (int)(start_x / BLOCK);
	map_y = (int)(start_y / BLOCK);
	
	// Distance à parcourir pour traverser une case
	delta_dist_x = fabsf(1.0f / dx);
	delta_dist_y = fabsf(1.0f / dy);
	
	// Direction et distance jusqu'au prochain bord de case
	if (dx < 0)
	{
		step_x = -1;
		side_dist_x = (start_x / BLOCK - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0f - start_x / BLOCK) * delta_dist_x;
	}
	
	if (dy < 0)
	{
		step_y = -1;
		side_dist_y = (start_y / BLOCK - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0f - start_y / BLOCK) * delta_dist_y;
	}
	
	// Algorithme DDA
	hit = 0;
	side = 0;
	
	while (hit == 0)
	{
		// Avancer dans la direction la plus proche
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Vérifier si on a touché un mur
		if (map_x < 0 || map_y < 0 || 
			map_y >= game->config.map_height ||
			map_x >= (int)ft_strlen(game->config.map[map_y]) ||
			game->config.map[map_y][map_x] == '1')
		{
			hit = 1;
		}
	}
	
	// Calculer la distance perpendiculaire
	if (side == 0)
		result.distance = (map_x - start_x / BLOCK + (1 - step_x) / 2) / dx;
	else
		result.distance = (map_y - start_y / BLOCK + (1 - step_y) / 2) / dy;
	
	result.distance *= BLOCK;
	result.side = side;
	
	// Calculer la coordonnée exacte de l'impact
	float wall_x;
	if (side == 0)
		wall_x = start_y + result.distance * dy / BLOCK;
	else
		wall_x = start_x + result.distance * dx / BLOCK;
	wall_x -= floor(wall_x);
	result.wall_x = wall_x;
	
	// Déterminer la texture à utiliser en fonction de la direction
	if (side == 0)
	{
		if (dx < 0)
			result.tex_num = 3; // WEST
		else
			result.tex_num = 2; // EAST
	}
	else
	{
		if (dy < 0)
			result.tex_num = 0; // NORTH
		else
			result.tex_num = 1; // SOUTH
	}
	
	return result;
}

static void	cast_ray(t_game *game, t_player *player, float angle, int x)
{
	t_ray_hit	hit;
	float		wall_height;
	int			wall_start, wall_end;
	int			y;
	int			tex_x, tex_y;
	int			color;
	float		step;
	float		tex_pos;
	t_texture	*tex;
	
	// Calculer la distance et informations sur le mur touché
	hit = calculate_distance(game, player->x, player->y, angle);
	
	// Éviter division par zéro
	if (hit.distance < 0.1f)
		hit.distance = 0.1f;
	
	// Calculer la hauteur du mur en pixels
	wall_height = (BLOCK * HEIGHT) / (hit.distance * 2.0f);
	
	// Limiter la hauteur pour éviter les débordements
	if (wall_height > HEIGHT * 3)
		wall_height = HEIGHT * 3;
	
	// Calculer les limites du mur sur l'écran
	wall_start = (HEIGHT - wall_height) / 2;
	wall_end = wall_start + wall_height;
	
	// S'assurer que les limites sont dans l'écran
	if (wall_start < 0) wall_start = 0;
	if (wall_end > HEIGHT) wall_end = HEIGHT;
	
	// Calculer la position X dans la texture
	tex = &game->textures[hit.tex_num];
	tex_x = (int)(hit.wall_x * tex->width);
	
	// Inverser la coordonnée X pour certaines faces (pour un rendu cohérent)
	if ((hit.side == 0 && cosf(angle) > 0) || (hit.side == 1 && sinf(angle) < 0))
		tex_x = tex->width - tex_x - 1;
	
	// Calculer le pas et la position initiale pour parcourir la texture
	step = (float)tex->height / wall_height;
	tex_pos = (wall_start - (HEIGHT - wall_height) / 2) * step;
	
	// Dessiner la colonne de pixels du mur avec texture
	y = wall_start;
	while (y < wall_end)
	{
		// Calculer la coordonnée Y de la texture
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		
		// Récupérer la couleur du pixel dans la texture
		color = *(int*)(tex->data + tex_y * tex->size_line + tex_x * (tex->bpp / 8));
		
		// Assombrir légèrement les murs Y (effet d'éclairage)
		if (hit.side == 1)
			color = (color >> 1) & 0x7F7F7F; // Diviser par 2
		
		// Dessiner le pixel
		put_pixel(game, x, y, color);
		y++;
	}
}

int	load_textures(t_game *game)
{
	int	width;
	int	height;
	int	i;

	if (!game->config.no_path || !game->config.so_path || 
		!game->config.we_path || !game->config.ea_path)
		return (0);
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, 
		game->config.no_path, &width, &height);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, 
		game->config.so_path, &width, &height);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, 
		game->config.we_path, &width, &height);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, 
		game->config.ea_path, &width, &height);
	
	// Vérifier que les images ont été chargées et obtenir leurs données
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img)
			return (0);
		game->textures[i].data = mlx_get_data_addr(game->textures[i].img, 
			&game->textures[i].bpp, &game->textures[i].size_line, 
			&game->textures[i].endian);
		game->textures[i].width = width;
		game->textures[i].height = height;
		i++;
	}
	return (1);
}

int	raycast(t_game *game)
{
	t_player	*player;
	float		angle;
	int			i;
	static int	textures_loaded = 0;

	player = &game->player;
	limit_fps(game);
	
	// Chargement des textures lors du premier appel
	if (!textures_loaded)
	{
		textures_loaded = load_textures(game);
		// Précalculer les valeurs constantes
		game->fraction = PI / 3 / WIDTH;
		game->start_angle = player->angle - PI / 6;
	}
	
	if (game->debug_mode)
	{
		draw_debug_map(game);
		draw_debug_rays(game, player);
		return (0);
	}

	// Utiliser les valeurs précalculées
	game->start_angle = player->angle - PI / 6;
	angle = game->start_angle;
	
	// Boucle standard pour le raycasting
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(game, player, angle, i);
		angle += game->fraction;
		i++;
	}
	
	return (0);
}
