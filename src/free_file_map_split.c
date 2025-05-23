/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file_map_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:54:07 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/23 20:49:44 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(const char *message)
{
	write(2, message, ft_strlen(message));
	return (-1);
}

void	free_file(t_info *info)
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

void	free_map(t_info *info)
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
	if (info->no_path)
		free(info->no_path);
	if (info->so_path)
		free(info->so_path);
	if (info->we_path)
		free(info->we_path);
	if (info->ea_path)
		free(info->ea_path);
	if (info->f_color)
		free(info->f_color);
	if (info->c_color)
		free(info->c_color);
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
