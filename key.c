#include "../cub3d.h"

int key_press(int keycode, t_info *info)
{
    if (keycode == ESC_KEY)
        quit_program(info);
    else if (keycode == W_KEY)
        info->keys.w = 1;
    else if (keycode == A_KEY)
        info->keys.a = 1;
    else if (keycode == S_KEY)
        info->keys.s = 1;
    else if (keycode == D_KEY)
        info->keys.d = 1;
    else if (keycode == RIGHT_ARROW)
        info->keys.right = 1;
    else if (keycode == LEFT_ARROW)
        info->keys.left = 1;
    return (0);
}

int key_release(int keycode, t_info *info)
{
    if (keycode == W_KEY)
        info->keys.w = 0;
    else if (keycode == A_KEY)
        info->keys.a = 0;
    else if (keycode == S_KEY)
        info->keys.s = 0;
    else if (keycode == D_KEY)
        info->keys.d = 0;
    else if (keycode == RIGHT_ARROW)
        info->keys.right = 0;
    else if (keycode == LEFT_ARROW)
        info->keys.left = 0;
    return (0);
        
}
