#include "cub3d.h"
#include <stdio.h>

// int random_map[MAP_WIDTH][MAP_HEIGHT]=
// {
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

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

void initialize_map(t_info *info)
{
    info->map = NULL;                   // real map   

    // info->example_map = random_map;     // example map

    info->map_width = MAP_WIDTH;        // change after parsing
    info->map_height = MAP_HEIGHT;      // change after parsing
}

int	check_map_name(t_info *info, char *map_name)
{
	int	i;
	int	name_length;

	i = 0;
	name_length = ft_strlen(map_name);
	if(name_length < 5)
		return (-1);
	if((map_name[name_length - 4] == '.' ) &&
		(map_name[name_length - 3] == 'c' ) &&
		(map_name[name_length - 2] == 'u' ) &&
		(map_name[name_length - 1] == 'b'))
		return (1);
	return (-1);
}

int	map_parsing(t_info *info, char **argv)
{
	if (check_map_name(info, argv[1]) == -1)
		return(ft_error("Error: incorrect map extension\n"));
}

int main(int argc, char **argv)
{
    t_info info;

    (void)argc;
    (void)argv;
	if (argc != 2)
		return(ft_error("Error: wrong argument count\n"));
	if(map_parsing(&info, argv) == -1)
    initialize_map(&info);
    initialize_mlx(&info);
    mlx_hook(info.win.mlx_win, 17, 0L, quit_program, &info);
    mlx_loop(info.mlx);
}
