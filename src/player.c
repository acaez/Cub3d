#include "../inc/cub3D.h"

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

void	move_player(t_player *player)
{
	int		speed;
	float	angle;
	float	cos_angle;
	float	sin_angle;

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
