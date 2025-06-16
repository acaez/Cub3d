#include "../../inc/cub3D.h"

static void	handle_rotation(t_player *player)
{
	if (player->rot_left)
		player->angle -= player->rot_speed;
	if (player->rot_right)
		player->angle += player->rot_speed;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
}

static int	check_collision(t_player *player, float x, float y)
{
	if (touch_wall(player->game, x + COLLISION, y))
		return (1);
	if (touch_wall(player->game, x - COLLISION, y))
		return (1);
	return (0);
}

static void	move_forward_backward(t_player *player)
{
	float	dx;
	float	dy;
	float	dir;
	float	new_x;
	float	new_y;

	if (!player->key_up && !player->key_down)
		return ;
	dx = cos(player->angle);
	dy = sin(player->angle);
	if (player->key_up)
		dir = 1.0;
	else
		dir = -1.0;
	new_x = player->x + dx * player->speed * dir;
	new_y = player->y + dy * player->speed * dir;
	if (!check_collision(player, new_x, player->y))
		player->x = new_x;
	if (!check_collision(player, player->x, new_y))
		player->y = new_y;
}

static void	move_strafe(t_player *player)
{
	float	sx;
	float	sy;
	float	dir;
	float	new_x;
	float	new_y;

	if (!player->key_left && !player->key_right)
		return ;
	sx = cos(player->angle + PI / 2);
	sy = sin(player->angle + PI / 2);
	if (player->key_right)
		dir = 1.0;
	else
		dir = -1.0;
	new_x = player->x + sx * player->speed * dir;
	new_y = player->y + sy * player->speed * dir;
	if (!check_collision(player, new_x, player->y))
		player->x = new_x;
	if (!check_collision(player, player->x, new_y))
		player->y = new_y;
}

void	move_player(t_player *player)
{
	handle_rotation(player);
	move_forward_backward(player);
	move_strafe(player);
}
