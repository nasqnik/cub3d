/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:34:53 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/18 20:17:31 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	info->win.x = WINDOW_WIDTH;	 // example window width, change after parsing
	info->win.y = WINDOW_HEIGHT;	// example window height, change after parsing

	if (!info->mlx)
		error("mlx_init failed in initialize_mlx", info);
	info->win.mlx_win = mlx_new_window(info->mlx,
			info->win.x, info->win.y, "cub3D");
	if (!info->win.mlx_win)
		error("mlx_new_window failed in initialize_mlx", info);
}

// void initialize_map(t_info *info)
// {
//	 info->map = NULL;                   // real map   

//     // info->example_map = random_map;     // example map

//     info->map_width = MAP_WIDTH;        // change after parsing
//     info->map_height = MAP_HEIGHT;      // change after parsing
// }

int	check_file_name(char *file_name)
{
	int	i;
	int	name_length;

	i = 0;
	name_length = ft_strlen(file_name);
	if(name_length < 5)
		return (-1);
	if((file_name[name_length - 4] == '.' ) &&
		(file_name[name_length - 3] == 'c' ) &&
		(file_name[name_length - 2] == 'u' ) &&
		(file_name[name_length - 1] == 'b'))
		return (1);
	return (-1);
}

int	file_parsing(t_info *info, char *file_name)
{
	if (check_file_name(file_name) == -1)
		return(ft_error("Error\nIncorrect file extension\n"));
	if (create_local_file_copy(info, file_name) == -1)
		return(ft_error("Error\nCould not create local file copy\n"));
	if (get_scene_elements(info) == -1)
		return(ft_free_file("Error\nIncorrect scene elements\n", info));
	if (check_lines_before_map(info) == -1)
		return(ft_free_file("Error\nIncorrect input before map\n", info));
	if (convert_to_map(info) == -1)
		return(ft_free_file("Error\nIncorrect values in map\n", info));
	if (is_valid_map(info) == -1)
		return(ft_free_file("Error\nNot a valid map\n", info));
	return (0);
}

void	init_file_info(t_info *info)
{
	info->map = NULL;
	info->file_copy = NULL;
	info->NO_path = NULL;
	info->SO_path = NULL;
	info->WE_path = NULL;
	info->EA_path = NULL;
	info->F_color = NULL;
	info->C_color = NULL;
	info->element_count = 0;
	info->pos_last_element = 0;
	info->pos_map_start = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->player.x = -1;
	info->player.y = 0;
	info->player.dir = 0;
}

int main(int argc, char **argv)
{
	t_info info;

	(void)argc;
	(void)argv;
	if (argc != 2)
		return(ft_error("Error\nWrong argument count\n"));
	init_file_info(&info);
	if(file_parsing(&info, argv[1]) == -1)
		return (1);
	// initialize_map(&info);
	// initialize_mlx(&info);
	// mlx_hook(info.win.mlx_win, 17, 0L, quit_program, &info);
	// mlx_loop(info.mlx);
	printf("success\n");
}
