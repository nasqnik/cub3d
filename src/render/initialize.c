
#include "../cub3d.h"

void initialize_player(t_info *info)
{
    if (info->player.direction == 'N')
    {
        info->player.dir = (t_vector){0.0, -1.0};
        info->player.camera_plane = (t_vector){0.66, 0.0};
    }
    else if (info->player.direction == 'S')
    {
        info->player.dir = (t_vector){0.0, 1.0};
        info->player.camera_plane = (t_vector){-0.66, 0.0};
    }
    else if (info->player.direction == 'E')
    {
        info->player.dir = (t_vector){1.0, 0.0};
        info->player.camera_plane = (t_vector){0.0, 0.66};
    }
    else if (info->player.direction == 'W')
    {
        info->player.dir = (t_vector){-1.0, 0.0};
        info->player.camera_plane = (t_vector){0.0, -0.66};
    }
}

void initialize_keys(t_info *info)
{
    info->keys.w = 0;
    info->keys.a = 0;
    info->keys.s = 0;
    info->keys.d = 0;
    info->keys.right = 0;
    info->keys.left = 0;
}

void initialize_cub3d(t_info *info)
{
    info->time = current_time();
    info->old_time = info->time;
    info->delta_time = 0.0;

    info->move_speed = 0.0;
    info->rot_speed = 0.0;

    initialize_player(info);
    initialize_keys(info);

    mlx_hook(info->mlx_win, 17, 0L, quit_program, info);
    mlx_hook(info->mlx_win, 2, 1L<<0, key_press, info);
    mlx_hook(info->mlx_win, 3, 1L<<1, key_release, info);  
    mlx_loop_hook(info->mlx, render_cub3d, info);
}
