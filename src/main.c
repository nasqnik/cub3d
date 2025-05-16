#include "cub3d.h"
#include <stdio.h> // Delete before submission

void initialize_mlx(t_info *info)
{
    info->mlx = mlx_init();

    info->win.x = WINDOW_WIDTH;         // example window width, change after parsing
    info->win.y = WINDOW_HEIGHT;        // example window height, change after parsing

    if (!info->mlx)
        error("mlx_init failed in initialize_mlx", info);
    info->win.mlx_win = mlx_new_window(info->mlx,
            info->win.x, info->win.y, "cub3D");
    if (!info->win.mlx_win)
        error("mlx_new_window failed in initialize_mlx", info);
}

int main(int argc, char **argv)
{
    t_info info;

    (void)argc;
    (void)argv;

    initialize_example_map(&info); // delete after parsing
    initialize_cub3d(&info);      // modify after parsing
    
    initialize_mlx(&info);
    mlx_hook(info.win.mlx_win, 17, 0L, quit_program, &info);
    mlx_loop(info.mlx);
}