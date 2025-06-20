/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 12:56:53 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	load_texture_image(t_tex_ctx *ctx)
{
	t_texture	*tex;

	tex = &ctx->game->textures[ctx->index];
	tex->img = mlx_xpm_file_to_image(ctx->game->mlx,
			ctx->path, ctx->w, ctx->h);
	if (!tex->img)
		return (0);
	tex->data = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->size_line, &tex->endian);
	tex->width = *ctx->w;
	tex->height = *ctx->h;
	return (1);
}

int	load_textures(t_game *game)
{
	int			w;
	int			h;
	t_tex_ctx	ctx;

	if (!game->config.no_path || !game->config.so_path
		|| !game->config.we_path || !game->config.ea_path)
		return (0);
	ctx = (t_tex_ctx){game, 0, game->config.no_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 1, game->config.so_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 2, game->config.we_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	ctx = (t_tex_ctx){game, 3, game->config.ea_path, &w, &h};
	if (!load_texture_image(&ctx))
		return (0);
	return (1);
}
