#include "../inc/cub3D.h"

//========================KEY=======================//

void	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->rot_left = true;
	if (keycode == RIGHT)
		player->rot_right = true;
	if (keycode == ESC)
		exit(0);
	
}

void	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->rot_left = false;
	if (keycode == RIGHT)
		player->rot_right = false;
}
//========================PLAYER=======================//

void move_player(t_player *player)
{
	int speed;
	float angle;
	float cos_angle;
	float sin_angle;

	speed = 3;
	angle = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->rot_left)
		player->angle -= angle;
	if (player->rot_right)
		player->angle += angle;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_right)
	{
		player->x -= cos_angle * speed;
		player->y += sin_angle * speed;
	}
	
}

//========================IMAGE=======================//
void	put_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		int index;

		index = y * game->size_line + x * (game->bpp / 8);
		game->data[index] = color & 0xFF;
		game->data[index + 1] = (color >> 8) & 0xFF;
		game->data[index + 2] = (color >> 16) & 0xFF;
	}
}

void	draw_square(t_game *game, int x, int y, int size, int color)
{
    int	i;
    int	j;
    
    i = 0;
    while (i < size)
    {
        put_pixel(game, x + i, y, color);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(game, x + i, y + size, color);
        i++;
    }
    j = 0;
    while (j < size)
    {
        put_pixel(game, x, y + j, color);
        j++;
    }
    j = 0;
    while (j < size)
    {
        put_pixel(game, x + size, y + j, color);
        j++;
    }
}

void clear_image(t_game *game)
{
	int i;

	i = 0;
	while (i < WIDTH * HEIGHT * (game->bpp / 8))
	{
		game->data[i] = 0;
		i++;
	}
}
//========================MAP=======================//

char **get_map(void)
{
    char **map;

    map = (char **)malloc(sizeof(char *) * 11);
    if (!map)
        return (NULL);
    map[0] = ft_strdup("111111111111111111");
    map[1] = ft_strdup("100000000000000001");
    map[2] = ft_strdup("100000000000000001");
    map[3] = ft_strdup("100000000000000001");
    map[4] = ft_strdup("100000000100000001");
	map[5] = ft_strdup("100000000000000001");
    map[6] = ft_strdup("100000000000010001");
	map[7] = ft_strdup("100000100000000001");
	map[8] = ft_strdup("100000011000000001");
	map[9] = ft_strdup("100000000000000001");
	map[10] = ft_strdup("111111111111111111");
    map[11] = NULL;
    return (map);
}
void draw_map(t_game *game)
{
	char **map;
	int  color;
	int x;
	int y;

	map = game->map;
	if (!map)
		return ;
	color = 0xFFFFFF;
	y = 0;
	while(map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, color);
			x++;
		}
		y++;
	}
}
//========================INIT=======================//
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->map = get_map();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->speed = 5.0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rot_left = false;
	player->rot_right = false;
}

//========================MAIN=======================//

bool touch_wall(t_game *game, float px, float py)
{
	int x;
	int y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float distance(float dx, float dy)
{
	return sqrt(dx * dx + dy * dy);
}

float fix_fish(t_game *game, float x1, float y1, float x2, float y2)
{
	float dx;
	float dy;
	float angle;
	float fish;

	dx = x2 - x1;
	dy = y2 - y1;
	angle = atan2(dy, dx) - game->player.angle;
	fish = distance(dx, dy) * cos(angle);
	return fish;
}

void draw_line(t_game *game, t_player *player, float start_x, int i)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;
	float dist;
	float height;
	int   start_y;
	int   end;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch_wall(game, ray_x, ray_y))
	{
		if (DEBGUG)
			put_pixel(game, ray_x, ray_y, 0x00FF00);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBGUG)
	{
		dist = fix_fish(game, player->x, player->y, ray_x, ray_y);
		height = (BLOCK / dist) * (WIDTH / 2);
		start_y = (HEIGHT - height) / 2;
		end = start_y + height;
		while (start_y < end)
		{
			put_pixel(game, i, start_y, 255);
			start_y++;
		}
	}
	
}

int draw_loop(t_game *game)
{
	t_player *player;
	float 	ray_x;
	float 	ray_y;
	float 	cos_angle;
	float 	sin_angle;
	float   fraction;
	float   start_x;
	int    i;

	player = &game->player;
    move_player(&game->player);
    clear_image(game);
	if (DEBGUG)
	{
		draw_square(game, game->player.x, game->player.y, 10, 0xFF0000);
		draw_map(game);
	}
	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while (!touch_wall(game, ray_x, ray_y))
	{
		put_pixel(game, ray_x, ray_y, 0x00FF00);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - (PI / 6);
	i = 0;
	while (i < WIDTH)
	{
		draw_line(game, player, start_x, i);
		start_x += fraction;
		i++;
	}
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main(void)
{
    t_game game;

    init_game(&game);
    init_player(&game.player);
    mlx_hook(game.win, 2, 0, (void *)key_press, &game.player);
    mlx_hook(game.win, 3, 0, (void *)key_release, &game.player);
    mlx_loop_hook(game.mlx, draw_loop, &game);
    draw_square(&game, WIDTH / 2, HEIGHT / 2, 10, 0xFF0000);
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
    mlx_loop(game.mlx);
    mlx_destroy_image(game.mlx, game.img);
    mlx_destroy_window(game.mlx, game.win);
    //mlx_destroy_display(game.mlx); // Linux only, not needed for macOS
    free(game.mlx);
    return (0);
}
