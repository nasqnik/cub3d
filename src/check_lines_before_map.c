/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines_before_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:38:40 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/17 19:18:53 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_start(const char* line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	check_lines_before_map(t_info *info)
{
	int	i;

	i = info->pos_last_element;
	if (!info->file_copy[i])
		return (-1);
	while (info->file_copy[i])
	{
		if(!is_not_empty_line(info->file_copy[i]))
			i++;
		else
		{
			if(is_valid_map_start(info->file_copy[i]))
				break ;
			else
				return (ft_error("Error\nFound Incorrect Map Start\n"));
		}
	}
	if (!info->file_copy[i])
		return ((ft_error("Error\nCould not find map start\n")));
	info->pos_map_start = i;
	return (0);
}
