#include "../inc/cub3D.h"

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
	float  ray_x;
	float  ray_y;
	float  cos_angle;
	float  sin_angle;
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