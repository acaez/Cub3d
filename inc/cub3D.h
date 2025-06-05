#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../mlx/minilibx_opengl/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH  1280
# define HEIGHT 720
# define BLOCK  64
# define DEBUG 1
# define COLLISION_RADIUS 10.0


# define W      13
# define A      0
# define S      1
# define D      2
# define ESC    53
# define LEFT   123
# define RIGHT  124

# define PI     3.14159265359

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
}	t_game;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;   // Format 0xRRGGBB
	int		ceiling_color; // Format 0xRRGGBB
	char	**map;
	int		map_start_line; // index of map start
}	t_config;


// ============================== player.c ============================= //
void	key_press(int keycode, t_player *player);
void	key_release(int keycode, t_player *player);
void	move_player(t_player *player);

// ============================== image.c ============================== //
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	clear_image(t_game *game);

// ============================== map.c ================================ //
char	**get_map(void);
void	draw_map(t_game *game);

// ============================== raycast.c ============================ //
void	draw_line(t_game *game, t_player *player, float start_x, int i);
int		draw_loop(t_game *game);

// ============================== utils.c ============================== //
bool	touch_wall(t_game *game, float px, float py);
float	distance(float dx, float dy);
float	fix_fish(t_game *game, float x1, float y1, float x2, float y2);

// ============================== init.c =============================== //
void	init_game(t_game *game);
void	init_player(t_player *player);

#endif
