#include "cub3d.h"

int quit_program(t_info *info)
{
    free_example_map(info);
    mlx_destroy_window(info->mlx, info->mlx_win);
    exit(0);
    return (0);
}

void error(char *message, t_info *info)
{
    (void)info;
    // if (info->map != NULL)
    //     free_array(info->map);
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(message, 2); 
    exit(EXIT_FAILURE);
}