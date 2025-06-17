/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:43:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/17 16:27:26 by matsauva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# if defined(__linux__) || defined(__LINUX__)
#  include "../mlx/minilibx_linux/mlx.h"
#  define LINUX 1
# elif defined(__APPLE__) || defined(__MACOS__)
#  include "../mlx/minilibx_opengl/mlx.h"
#  define MACOS 1
# else
#  error "Unsupported platform: only Linux and macOS are supported"
# endif

# define WIDTH     1280
# define HEIGHT    720
# define BLOCK     64
# define PI        3.14159265359
# define ZONE_WIDTH 32
# define ZONE_HEIGHT 16
# ifdef LINUX
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define ESC 65307
#  define LEFT 65361
#  define RIGHT 65363
#  define TAB 65289
#  define KEY_PRESS_MASK    1
#  define KEY_RELEASE_MASK  2
#  define DESTROY_MASK      131072
# elif MACOS
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define ESC 53
#  define LEFT 123
#  define RIGHT 124
#  define TAB 48
#  define KEY_PRESS_MASK    0
#  define KEY_RELEASE_MASK  0
#  define DESTROY_MASK      0
# endif

# define ERR_TEXTURE_PATHS \
	"Config Validation : Missing texture paths (NO, SO, WE, EA)."
# define ERR_COLOR_MISSING \
	"Config Validation : Missing floor or ceiling color."
# define ERR_COLOR_IDENTICAL \
	"Config Validation : Floor and ceiling colors must differ."
# define ERR_MAP_INVALID_DIM \
	"Config Validation : Map missing or too small (minimum 3x3)."
# define ERR_MAP_INVALID_CHARS \
	"Map Validation : Map contains invalid characters."
# define ERR_PLAYER_COUNT \
	"Map Validation : Map must contain exactly one player position."
# define ERR_MAP_NOT_CLOSED \
	"Map Validation : Map is not properly closed by walls."

typedef struct s_config
{
	char	**map;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		sky_color;
	int		map_width;
	int		map_height;
}	t_config;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			speed;
	float			rot_speed;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			rot_left;
	bool			rot_right;
	t_config		config;
	struct s_game	*game;
}	t_player;

typedef struct s_minimap
{
	int		x;
	int		y;
	int		size;
	int		color;
	int		map_w;
	int		map_h;
	int		cell_size;
	int		origin_x;
	int		origin_y;
	float	scale;
	int zone_x;
	int zone_y;
}	t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		**map;
	int			bpp;
	int			size_line;
	int			endian;
	bool		debug_mode;
	t_player	player;
	t_config	config;
	t_minimap	minimap;
}	t_game;

typedef struct s_debug_map
{
	int		scale;
	int		offset_x;
	int		offset_y;
}	t_debug_map;

typedef struct s_ray
{
	t_game	*game;
	t_player *player;
	int		i;
	int		wall_color;
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	int		max_steps;
	int		steps;
	float	height;
}	t_ray;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_tile_ctx
{
	t_game		*game;
	t_minimap	*minimap;
	int			start_x;
	int			start_y;
}	t_tile_ctx;

/* ============================== GAME  =================================== */
/* ------------------------------ exit.c ---------------------------------- */
void	free_map(char **map);
void	free_config(t_config *cfg);
void	exit_error(t_game *game, char *msg);
int		close_window(t_game *game);

/* ------------------------------ game.c ---------------------------------- */
void	clear_image(t_game *game);
void	draw_scene(t_game *game);
int		game_loop(t_game *game);

/* ------------------------------ init.c ---------------------------------- */
void	init_game(t_game *game, int argc, char **argv);

/* ============================== PARSING ================================= */
/* ------------------------------ get_map.c ------------------------------- */
bool	pad_map_in_place(char **map, size_t max_len, char pad);
int		get_map_height(char **map);
int		get_map_width(char **map);

/* ------------------------------ map.c ----------------------------------- */
void	draw_minimap(t_game *game);

/* ------------------------------ parse.c --------------------------------- */
bool	parse_cub_file(t_config *cfg, char *path, char **err);

/* ------------------------------ valid.c --------------------------------- */
bool	validate_map(char **map, char **err);
bool	validate_config(t_config *cfg, char **err);

/* ============================== PLAYER ================================== */
/* ------------------------------ keys.c ---------------------------------- */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

/* ------------------------------ move.c ---------------------------------- */
void	move_player(t_player *player);

/* ============================== RAYCAST ================================= */
/* ------------------------------ debug_mode.c ---------------------------- */
void	draw_debug_rays(t_game *game, t_player *player);
void	draw_debug_map(t_game *game);

/* ------------------------------ raycast.c ------------------------------- */
void	put_pixel(t_game *game, int x, int y, int color);
int		raycast(t_game *game);

/* ============================== UTILITY ================================= */
/* ------------------------------ debug_mode_utils.c ---------------------- */
void	draw_debug_background(t_game *game);
int		calculate_debug_scale(t_game *game, int *offset_x, int *offset_y);
void	draw_debug_cell(t_game *game, int x, int y, t_debug_map *dm);
void	draw_debug_player(t_game *game, t_debug_map *dm);
void	draw_debug_impact(t_game *game, float ray_x, float ray_y,
		t_debug_map *dm);

/* ------------------------------ debug_utils.c --------------------------- */
void	print_config(const t_config *cfg);
void	print_map(char **map);

/* ------------------------------ draw_utils.c ---------------------------- */
void	setup_dir(t_game *game, char direction);
void	setup_pos(t_game *game);

/* ------------------------------ pars_utils.c ---------------------------- */
char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool	is_map_line(char *line);
bool	parse_color(char *line, int *color);
bool	set_texture(t_config *cfg, const char *id, const char *path);
/* ------------------------------ pars_utils2.c ---------------------------- */
void	copy_normalized_spaces(const char *src, char *dst);
char	*normalize_spaces(char *str);
bool	is_empty_line(const char *line);
char	*remove_trailing_newline(char *line);
/* ------------------------------ pars_utils3.c ---------------------------- */
bool	parse_line(t_config *cfg, char *line);
bool	add_line_to_map(t_config *cfg, char *line, int *sz, int *cap);
bool	read_map_lines(t_config *cfg, int fd, char *line);
bool	handle_trailing_lines(int fd, char **err);
/* ------------------------------ map_utils.c ---------------------------- */
void	draw_filled_square(t_game *game, t_square sq);
void	init_minimap(t_game *game, t_minimap *m);
/* ------------------------------ raycast_utils.c ------------------------- */
float	distance(float dx, float dy);
float	fixed_dist(t_ray *r);
int		check_collision(t_config *config, float x, float y);

/* ------------------------------ valide_utils.c -------------------------- */
bool	is_inside_map(char **map, int y, int x);
bool	is_open_char(char c);
bool	line_has_only_valid(char *s);

/* ------------------------------ init_utils.c ---------------------------- */
void	init_config(t_config *cfg);
void	init_key(t_game *game);
void	setup_dir(t_game *game, char direction);
void	setup_pos(t_game *game);
void	init_player(t_player *player, t_game *game);

#endif
