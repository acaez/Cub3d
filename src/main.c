#include "../inc/cub3D.h"

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
