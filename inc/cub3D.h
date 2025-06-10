
#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# ifdef __linux__
#  include "../mlx/minilibx_linux/mlx.h"
#  define LINUX 1
# elif __APPLE__
#  include "../mlx/minilibx_opengl/mlx.h"
#  define MACOS 1
# endif

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0
# define COLLISION_RADIUS 1.0

#  define W   119
#  define A   97
#  define S   115
#  define D   100
#  define ESC  65307
#  define LEFT  65361
#  define RIGHT 65363
/*
# ifdef LINUX
#  define W   119
#  define A   97
#  define S   115
#  define D   100
#  define ESC  65307
#  define LEFT  65361
#  define RIGHT 65363
# elif MACOS
#  define W   13
#  define A   0
#  define S   1
#  define D   2
#  define ESC  53
#  define LEFT  123
#  define RIGHT 124
# endif
*/
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
	int     map_width;       // largeur max après padding
    int     map_height;      // nombre de lignes
}	t_config;

typedef struct s_game
{
	void		*mlx;			// Pointeur vers le contexte MLX (mlx_init)
	void		*win;			// Fenêtre MLX (créée avec mlx_new_window)
	void		*img;			// Image actuelle à dessiner (mlx_new_image)
	char		*data;			// Données brutes de l'image (accès pixel par pixel)
	int			bpp;			// Bits par pixel de l'image (généralement 32)
	int			size_line;		// Nombre d’octets par ligne de l’image
	int			endian;			// Endianness (0 = little endian)
	char		**map;			// Carte du niveau (tableau de chaînes)
	t_player	player;			// Joueur principal (position, direction, touches)
	struct s_config	*config;	// Configuration globale (textures, couleurs, carte brute)
}	t_game;

// ============================== player.c ============================= //
void	key_press(int keycode, t_player *player);
void	key_release(int keycode, t_player *player);
void	move_player(t_player *player);
// ============================== image.c ============================== //
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_filled_square(t_game *game, int x, int y, int size, int color);
void	clear_image(t_game *game);
// ============================== map.c ================================ //
char	**get_map(void);
void	draw_map(t_game *game);
void	draw_minimap(t_game *game);
// ============================== raycast.c ============================ //
void	draw_line(t_game *game, t_player *player, float start_x, int i);
int		draw_loop(t_game *game);
// ============================== utils.c ============================== //
bool	touch_wall(t_game *game, float px, float py);
float	distance(float dx, float dy);
float	fix_fish(t_game *game, float x1, float y1, float x2, float y2);

// ============================== init.c =============================== //
void	init_game(t_game *game);
void	init_config(t_config *cfg);
void	init_player_from_map(t_game *game);
// ============================== exit.c =============================== //
void	exit_with_error(t_game *game, char *msg);
void	exit_game(t_game *game, int exit_code);
int		exit_game_hook(t_game *game);
void	free_config(t_config *cfg);
void	free_map(char **map);
// ============================= parses.c ============================== //
bool	parse_cub_file(t_config *cfg, char *path);
// ========================== parses_utils.c =========================== //
char	*ft_strtrim_free(char *str, const char *set);
char	**ft_realloc_tab(char **old, int new_size);
bool    is_map_line(const char *line);
int     parse_color(char *line);
void    set_texture(t_config *cfg, char *id, char *path);
// =========================== map_utils.c ============================= //
size_t  get_max_line_len(char **map);
bool    pad_map_in_place(char **map, size_t max_len, char pad);
int     get_map_height(char **map);
// ============================ validate.c ============================= //
bool	validate_map(char **map);
// ========================= validate_utils.c ========================== //
bool    is_inside_map(char **map, int y, int x);
bool    is_open_char(char c);
bool	line_has_only_valid(char *s);
#endif