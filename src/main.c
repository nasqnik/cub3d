
#include "cub3d.h"

void initialize_mlx(t_info *info)
{
    info->mlx = mlx_init();       // example window height, change after parsing

    if (!info->mlx)
        error("mlx_init failed in initialize_mlx", info);
    info->mlx_win = mlx_new_window(info->mlx,
            WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    if (!info->mlx_win)
        error("mlx_new_window failed in initialize_mlx", info);
}

int main(int argc, char **argv)
{
    t_info info;

    (void)argc;
    (void)argv;

    initialize_mlx(&info);

    initialize_example_map(&info);      // delete after parsing
    initialize_cub3d(&info);            // modify after parsing

    mlx_loop(info.mlx);
}