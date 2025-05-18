#include "cub3d.h"


// int quit_program(t_info *info)
// {
//     mlx_destroy_window(info->mlx, info->win.mlx_win);
// 	// if (info->map != NULL)
// 	// 	free_array(info->map);
// 	exit(EXIT_SUCCESS);
// }

int	ft_error(const char *message)
{
	write(2, message, ft_strlen(message));
	return (-1);
}

void free_file(t_info *info)
{
	int	i;

	i = 0;
	while (info->file_copy[i])
	{
		free(info->file_copy[i]);
		info->file_copy[i] = NULL;
		i++;
	}
	free(info->file_copy);
	info->file_copy = NULL;
}

void free_map(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->map_height)
	{
		free(info->map[i]);
		info->map[i] = NULL;
		i++;
	}
	free(info->map);
	info->map = NULL;
}

int	ft_free_file(const char *message, t_info *info)
{
	if (info->file_copy)
		free_file(info);
	if (info->map)
		free_map(info);
	if (info->NO_path)
		free(info->NO_path);
	if (info->SO_path)
		free(info->SO_path);
	if (info->WE_path)
		free(info->WE_path);
	if (info->EA_path)
		free(info->EA_path);
	if (info->F_color)
		free(info->F_color);	
	if (info->C_color)
		free(info->C_color);
	return (ft_error(message));
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
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