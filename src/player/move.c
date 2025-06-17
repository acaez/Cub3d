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

static void	move_forward(t_player *player)
{ 
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->x + cos(player->angle) * player->speed;
		new_y = player->y + sin(player->angle) * player->speed;
		if (check_collision(&player->config, new_x, new_y))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

void	move_player(t_player *player)
{
	handle_rotation(player);
	move_forward(player);
}
