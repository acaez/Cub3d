/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsauva <matsauva@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:43:00 by matsauva          #+#    #+#             */
/*   Updated: 2025/06/20 15:14:20 by matsauva         ###   ########.fr       */
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
# include <time.h>
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
# define BLOCK     128
# define PI        3.14159265359
# define ZONE_WIDTH 32
# define ZONE_HEIGHT 16
# define MINIMAP_W_RATIO 0.2
# define MINIMAP_H_RATIO 0.2
# ifdef LINUX
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define ESC 65307
#  define SPACE 32
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
#  define SPACE 49
#  define KEY_PRESS_MASK    0
#  define KEY_RELEASE_MASK  0
#  define DESTROY_MASK      0
# endif

# define ERR_TEXTURE_MISSING_FILE \
	"Config Validation : Missing texture file"
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

#define PAUSE_MSG1 "GAME PAUSED"
#define PAUSE_MSG2 "PRESS ESC TO QUIT, SPACE TO RESUME"
#define PAUSE_TXT1_X 605
#define PAUSE_TXT1_Y 354
#define PAUSE_TXT2_X 530
#define PAUSE_TXT2_Y 374
#define PAUSE_RECT_W 480
#define PAUSE_RECT_H 48

typedef struct s_trigo
{
	float	*cos_table;
	float	*sin_table;
	int		table_size;
}	t_trigo;

typedef struct s_ray_hit
{
	float	distance;
	int		side;
	float	wall_x;
	int		tex_num;
}	t_ray_hit;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

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
	t_trigo		trigo;
	clock_t		last_frame;
	t_texture	textures[4];
	float		fraction;
	float		start_angle;
	bool	paused;
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
	float	angle; 
	float	cos_angle;
	float	sin_angle;
	int		max_steps;
	int		steps;
	float	height;
}	t_ray;

typedef struct s_ray_ctx {
	float		start_x;
	float		start_y;
	float		angle;
	float		dx;
	float		dy;
	int			map_x;
	int			map_y;
	float		delta_x;
	float		delta_y;
	int			step_x;
	int			step_y;
	float		side_x;
	float		side_y;
	int			side;
	float		wall_x;
}	t_ray_ctx;

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

typedef struct s_step_ctx {
	int	map_pos;
	int	*step;
	float	*side_dist;
}	t_step_ctx;

typedef struct s_dda_ctx {
	int	*map_x;
	int	*map_y;
	float	*side_x;
	float	*side_y;
	float	delta_x;
	float	delta_y;
	int	*step_x;
	int	*step_y;
	int	*side;
}	t_dda_ctx;

typedef struct s_draw_ctx {
	t_texture	*tex;
	t_ray_hit	*hit;
	int			x;
	int			wall_start;
	int			wall_end;
	int			tex_x;
}	t_draw_ctx;

typedef struct s_tex_ctx
{
	t_game	*game;
	int		index;
	char	*path;
	int		*w;
	int		*h;
}	t_tex_ctx;

typedef struct s_cast_ctx
{
	t_ray_hit	hit;
	t_texture	*tex;
	float		wall_height;
	int			wall_start;
	int			wall_end;
	int			tex_x;
	t_ray_ctx	ray;
}	t_cast_ctx;

/* ============================== GAME  =================================== */
/* ------------------------------ exit.c ---------------------------------- */
void	exit_error(t_game *game, char *msg);
int		close_window(t_game *game);
/* ------------------------------ free.c ---------------------------------- */
void	free_map(char **map);
void	free_config(t_config *cfg);
void	free_trigo(t_trigo *trigo);
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
void	draw_map_tile(t_tile_ctx *ctx, int x, int y);

/* ------------------------------ parse.c --------------------------------- */
bool	parse_cub_file(t_config *cfg, char *path, char **err);

/* ------------------------------ valid.c --------------------------------- */
bool	validate_map(char **map, char **err);
bool	validate_config(t_config *cfg, char **err);

/* ============================== PLAYER ================================== */
/* ------------------------------ keys.c ---------------------------------- */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_move(int x, int y, void *param);
void	draw_crosshair(t_game *game);

/* ------------------------------ move.c ---------------------------------- */
void	move_player(t_player *player);

/* ============================== RAYCAST ================================= */
/* ------------------------------ debug_mode.c ---------------------------- */
void	draw_debug_rays(t_game *game, t_player *player);
void	draw_debug_map(t_game *game);

/* ------------------------------ raycast.c ------------------------------- */
t_ray_hit	calculate_distance(t_game *game, t_ray_ctx *ctx);
int		raycast(t_game *game);
int		load_textures(t_game *game);
/* ----------------------------- cast_ray.c ------------------------------- */
void	cast_ray(t_game *game, t_ray_ctx *ray, int x);
/* ----------------------------- ray_math.c ------------------------------- */
void	setup_ray_ctx(t_game *game, t_ray_ctx *ctx);
int		get_texture_index(int side, float dx, float dy);
float	compute_distance(float start, int map_pos, int step, float dir);
/* ----------------------------- ray_hit.c -------------------------------- */
t_ray_hit	calculate_distance(t_game *game, t_ray_ctx *ctx);
/* -------------------------- texture_loader------------------------------- */
int	load_textures(t_game *game);

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
void	draw_pause_overlay(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_crosshair(t_game *game);
/* ------------------------------ pars_utils.c ---------------------------- */
char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool	is_map_line(char *line);
bool	parse_color(char *line, int *color);
bool	set_texture(t_config *cfg, const char *id, const char *path);
/* ------------------------------ pars_utils2.c --------------------------- */
void	copy_normalized_spaces(const char *src, char *dst);
char	*normalize_spaces(char *str);
bool	is_empty_line(const char *line);
char	*remove_trailing_newline(char *line);
/* ------------------------------ pars_utils3.c --------------------------- */
bool	parse_line(t_config *cfg, char *line);
bool	add_line_to_map(t_config *cfg, char *line, int *sz, int *cap);
bool	read_map_lines(t_config *cfg, int fd, char *line);
bool	handle_trailing_lines(int fd, char **err);
/* ------------------------------ map_utils.c ----------------------------- */
void	draw_filled_square(t_game *game, t_square sq);
void	draw_tile_line(t_tile_ctx *ctx, int y, int end_x);
void	init_minimap(t_game *game);

/* ------------------------------ raycast_utils.c ------------------------- */
void	get_trigo_value(t_trigo *trigo, float angle, float *cos_val, float *sin_val);
void	limit_fps(t_game *game);
int		check_collision(t_config *config, float x, float y);
/* ----------------------------- raycast_utils2.c ------------------------- */
float	distance(float dx, float dy);
float	fixed_dist(t_ray *r);
/* ------------------------------ valide_utils.c -------------------------- */
bool	is_inside_map(char **map, int y, int x);
bool	is_open_char(char c);
bool	line_has_only_valid(char *s);
bool	file_exists(char *path);
/* ------------------------------ init_utils.c ---------------------------- */
void	init_config(t_config *cfg);
void	init_key(t_game *game);
void	setup_dir(t_game *game, char direction);
void	setup_pos(t_game *game);
void	init_player(t_player *player, t_game *game);
/* ------------------------------ key_utils.c ----------------------------- */
bool	handle_pause_keys(int keycode, t_game *game);
bool	handle_debug_keys(int keycode, t_game *game);
void	movement_keys(int keycode, t_game *game);

#endif
