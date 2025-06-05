#include "../inc/cub3D.h"

int	key_release(int keycode, void *param)
{
	t_player	*player = (t_player *)param;

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

	return (0);
}

int	key_press(int keycode, void *param)
{
	t_player	*player = (t_player *)param;

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

void	move_player2(t_player *player)
{
	float	dx = cos(player->angle);
	float	dy = sin(player->angle);
	float	sx = cos(player->angle + PI / 2);
	float	sy = sin(player->angle + PI / 2);

	float	new_x;
	float	new_y;

	// Rotation
	if (player->rot_left)
		player->angle -= player->rot_speed;
	if (player->rot_right)
		player->angle += player->rot_speed;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;

	// Avancer / Reculer
	if (player->key_up || player->key_down)
	{
		float dir = player->key_up ? 1.0 : -1.0;
		new_x = player->x + dx * player->speed * dir;
		new_y = player->y + dy * player->speed * dir;

		// Collision sur X
		if (!touch_wall(player->game, new_x + COLLISION_RADIUS, player->y) &&
			!touch_wall(player->game, new_x - COLLISION_RADIUS, player->y))
			player->x = new_x;

		// Collision sur Y
		if (!touch_wall(player->game, player->x, new_y + COLLISION_RADIUS) &&
			!touch_wall(player->game, player->x, new_y - COLLISION_RADIUS))
			player->y = new_y;
	}

	// Strafe gauche / droite
	if (player->key_left || player->key_right)
	{
		float dir = player->key_right ? -1.0 : 1.0;
		new_x = player->x + sx * player->speed * dir;
		new_y = player->y + sy * player->speed * dir;

		// Collision sur X
		if (!touch_wall(player->game, new_x + COLLISION_RADIUS, player->y) &&
			!touch_wall(player->game, new_x - COLLISION_RADIUS, player->y))
			player->x = new_x;

		// Collision sur Y
		if (!touch_wall(player->game, player->x, new_y + COLLISION_RADIUS) &&
			!touch_wall(player->game, player->x, new_y - COLLISION_RADIUS))
			player->y = new_y;
	}
}
