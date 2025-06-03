#include "../inc/cub3D.h"

char	**get_map(void)
{
	char	**map;

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

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	if (!map)
		return ;
	color = 0xFFFFFF;
	y = 0;
	while (map[y])
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
