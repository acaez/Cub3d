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
	int		floor_color;   // Format 0xRRGGBB
	int		ceiling_color; // Format 0xRRGGBB
	char	**map;
	int		map_start; // index of map start
	int		map_width;  // Width of the map
	int		map_height; // Height of the map
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


// ============================== exit.c ============================= //
void	free_map(char **map);
void	exit_error(t_game *game, char *msg);
int		close_window(t_game *game);
// ============================== game.c ============================== //
void	draw_scene(t_game *game);
int		game_loop(t_game *game);
// ============================== image.c ================================ //
void	clear_image(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_filled_square(t_game *game, int x, int y, int size, int color);
// ============================== init.c ============================ //
void	init_key(t_game *game);
void	init_player(t_player *player, t_game *game);
void	init_config(t_config *cfg);
void	init_game(t_game *game);
// ============================== key.c ============================== //
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
// ============================== map.c =============================== //
char	**get_map(void);
void	draw_map(t_game *game);
void	draw_minimap(t_game *game);
// ============================== move.c =============================== //
void	move_player(t_player *player);
// ============================== utils.c ============================== //
float	distance(float dx, float dy);
float	fix_fish(t_game *game, float x1, float y1, float x2, float y2);
bool	touch_wall(t_game *game, float px, float py);

// ============================== parse.c ============================== //
bool    parse_cub_file(t_config *cfg, char *path);

// ============================== parse_utils.c ============================== //
char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool    is_map_line(const char *line);
void    set_texture(t_config *cfg, char *id, char *path);
int     parse_color(char *line);

// ============================== valid_utils.c ============================== //
bool    is_inside_map(char **map, int y, int x);
bool    is_open_char(char c);
bool    line_has_only_valid(char *s);
bool    validate_map(char **map);

#endif
