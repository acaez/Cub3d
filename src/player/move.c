#include "../../inc/cub3D.h"

void	move_player(t_player *player)
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

	// Forward / Backward movement
	if (player->key_up || player->key_down)
	{
		float dir = player->key_up ? 1.0 : -1.0;
		new_x = player->x + dx * player->speed * dir;
		new_y = player->y + dy * player->speed * dir;

		// Collision detection on X axis
		if (!touch_wall(player->game, new_x + COLLISION, player->y) &&
			!touch_wall(player->game, new_x - COLLISION, player->y))
			player->x = new_x;

		// Collision detection on Y axis
		if (!touch_wall(player->game, player->x, new_y + COLLISION) &&
			!touch_wall(player->game, player->x, new_y - COLLISION))
			player->y = new_y;
	}

	// Strafe left / right
	if (player->key_left || player->key_right)
	{
		float dir = player->key_right ? -1.0 : 1.0;
		new_x = player->x + sx * player->speed * dir;
		new_y = player->y + sy * player->speed * dir;

		// Collision detection on X axis
		if (!touch_wall(player->game, new_x + COLLISION, player->y) &&
			!touch_wall(player->game, new_x - COLLISION, player->y))
			player->x = new_x;

		// Collision detection on Y axis
		if (!touch_wall(player->game, player->x, new_y + COLLISION) &&
			!touch_wall(player->game, player->x, new_y - COLLISION))
			player->y = new_y;
	}
}
