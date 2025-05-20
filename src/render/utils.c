#include "../cub3d.h"

int quit_program(t_info *info)
{
    ft_free_file("thanks for playing\n", info); // check this
    mlx_destroy_window(info->mlx, info->mlx_win);
    exit(0);
    return (0);
}


double current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}