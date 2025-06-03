#include "../inc/cub3D.h"

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