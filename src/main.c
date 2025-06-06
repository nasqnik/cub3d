/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:01:39 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/22 22:26:20 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(char *file_name)
{
	int	name_length;

	name_length = ft_strlen(file_name);
	if (name_length < 5)
		return (-1);
	if ((file_name[name_length - 4] == '.' )
		&& (file_name[name_length - 3] == 'c' )
		&& (file_name[name_length - 2] == 'u' )
		&& (file_name[name_length - 1] == 'b'))
		return (1);
	return (-1);
}

int	file_parsing(t_info *info, char *file_name)
{
	if (check_file_name(file_name) == -1)
		return (ft_error("Error\nIncorrect file extension\n"));
	if (create_local_file_copy(info, file_name) == -1)
		return (ft_error("Error\nCould not create local file copy\n"));
	if (get_scene_elements(info) == -1)
		return (ft_free_file("Error\nIncorrect scene elements\n", info));
	if (check_lines_before_map(info) == -1)
		return (ft_free_file("Error\nIncorrect input before map\n", info));
	if (convert_to_map(info) == -1)
		return (ft_free_file("Error\nIncorrect values in map\n", info));
	if (is_valid_map(info) == -1)
		return (ft_free_file("Error\nNot a valid map\n", info));
	return (0);
}

void	init_file_info(t_info *info)
{
	info->map = NULL;
	info->file_copy = NULL;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->f_color = NULL;
	info->c_color = NULL;
	info->element_count = 0;
	info->pos_last_element = 0;
	info->pos_map_start = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->player.pos.x = -1;
	info->player.pos.y = 0;
	info->player.dir.x = 0;
	info->player.dir.y = 0;
	info->player.direction = 0;
}

void	initialize_mlx(t_info *info)
{
	int	bpp;
	int	line_length;
	int	endian;

	info->mlx = NULL;
	info->mlx_win = NULL;
	info->_img = NULL;
	info->_addr = NULL;
	info->mlx = mlx_init();
	if (!info->mlx)
		quit_program_message("mlx_init failed\n", info);
	info->mlx_win = mlx_new_window(info->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!info->mlx_win)
		quit_program_message("mlx_new_window failed\n", info);
	info->_img = mlx_new_image(info->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!info->_img)
		quit_program_message("mlx_new_image failed\n", info);
	info->_addr = mlx_get_data_addr(info->_img, &bpp, &line_length, &endian);
	if (!info->_addr)
		quit_program_message("mlx_get_data_addr failed\n", info);
	initialize_textures(info);
	load_textures(info);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		return (ft_error("Error\nWrong argument count\n"));
	init_file_info(&info);
	if (file_parsing(&info, argv[1]) == -1)
		return (1);
	initialize_mlx(&info);
	initialize_cub3d(&info);
	mlx_loop(info.mlx);
	printf("success\n");
}
