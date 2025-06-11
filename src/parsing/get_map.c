#include "../../inc/cub3D.h"

size_t  get_max_line_len(char **map)
{
    size_t  max_len;
    size_t  len;
    int     y;

    max_len = 0;
    y = 0;
    while (map[y])
    {
        len = ft_strlen(map[y]);
        if (len > max_len)
            max_len = len;
        y++;
    }
    return (max_len);
}

bool    pad_map_in_place(char **map, size_t max_len, char pad)
{
    size_t  len;
    int     y;
    char    *new_line;

    y = 0;
    while (map[y])
    {
        len = ft_strlen(map[y]);
        if (len < max_len)
        {
            new_line = ft_calloc(max_len + 1, 1);
            if (!new_line)
                return (false);
            ft_memcpy(new_line, map[y], len);
            ft_memset(new_line + len, pad, max_len - len);
            free(map[y]);
            map[y] = new_line;
        }
        y++;
    }
    return (true);
}

int     get_map_height(char **map)
{
    int h = 0;
    while (map[h])
        h++;
    return (h);
}
