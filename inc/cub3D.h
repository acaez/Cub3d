#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# if defined(__linux__) || defined(__LINUX__)
#  include "../mlx/minilibx_linux/mlx.h"
#  define LINUX 1
# elif defined(__APPLE__) || defined(__MACOS__)
#  include "../mlx/minilibx_opengl/mlx.h"
#  define MACOS 1
# endif

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 1
# define COLLISION 1.0

# ifdef LINUX
#  define W   119
#  define A   97
#  define S   115
#  define D   100
#  define ESC  65307
#  define LEFT  65361
#  define RIGHT 65363
#  define TAB  65289
# elif MACOS
#  define W   13
#  define A   0
#  define S   1
#  define D   2
#  define ESC  53
#  define LEFT  123
#  define RIGHT 124
#  define TAB  48
# endif

# define PI   3.14159265359

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	speed;
	float	rot_speed;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	rot_left;
	bool	rot_right;
	struct s_game *game;
}	t_player;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
}	t_config;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	t_player	player;
	t_config	config;
	bool        debug_mode;
}	t_game;


// ============================== GAME ================================ //
// ------------------------------ exit.c ------------------------------ //
void	free_map(char **map);
void	free_config(t_config *cfg);
void	exit_error(t_game *game, char *msg);
int		close_window(t_game *game);
// ------------------------------ init.c ------------------------------ //
void	init_key(t_game *game);
void	init_mlx(t_game *game);
void	init_player(t_player *player, t_game *game);
void	init_config(t_config *cfg);
void	init_game(t_game *game, int argc, char **argv);
// ------------------------------ raycast.c --------------------------- //
void	draw_scene(t_game *game);
int		game_loop(t_game *game);

// ============================== PARSING ============================= //
// ------------------------------ get_map.c --------------------------- //
size_t  get_max_line_len(char **map);
bool    pad_map_in_place(char **map, size_t max_len, char pad);
int     get_map_height(char **map);
// ------------------------------ map.c ------------------------------- //
char	**get_map(void);
void	draw_map(t_game *game);
void	draw_minimap(t_game *game);
// ------------------------------ parse.c ----------------------------- //
bool	parse_cub_file(t_config *cfg, char *path);
// ------------------------------ valid.c ----------------------------- //
bool    validate_map(char **map);
bool	validate_config(t_config *cfg);

// ============================== PLAYER ============================== //
// ------------------------------ draw.c ------------------------------ //
void	clear_image(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_filled_square(t_game *game, int x, int y, int size, int color);
// ------------------------------ keys.c ------------------------------ //
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
// ------------------------------ move.c ------------------------------ //
void	move_player(t_player *player);

// ============================== UTILS =============================== //
// ------------------------------ draw_utils.c ------------------------ //
void	setup_dir(t_game *game, char direction);
void	setup_pos(t_game *game);
// ------------------------------ pars_utils.c ------------------------ //
char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool    is_map_line(char *line);
bool	parse_color(char *line, int *color);
bool	set_texture(t_config *cfg, const char *id, const char *path);
// ------------------------------ utils.c ----------------------------- //
float	distance(float dx, float dy);
float	fix_fish(t_game *game, float x1, float y1, float x2, float y2);
bool	touch_wall(t_game *game, float px, float py);
// ------------------------------ valide_utils.c ---------------------- //
bool 	is_inside_map(char **map, int y, int x);
bool 	is_open_char(char c);
bool    line_has_only_valid(char *s);


#endif
