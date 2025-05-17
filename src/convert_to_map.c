/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:51:58 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/17 19:29:06 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_max_line_length(char **file)
{
	int	i;
	int	max_length;

	i = 0;
	max_length = 0;
	while (file[i])
	{
		if (ft_strlen(file[i]) > max_length)
			max_length = ft_strlen(file[i]);
		i++;
	}
	return (max_length);
}

int	convert_to_map(t_info *info)
{
	int	j;
	int	i;
	char c;
	
	i = 0;
	info->map_width = find_max_line_length(info->file_copy + info->pos_map_start);
	info->map_height = info->row_count - info->pos_map_start + 1;
	if (info->map_height < 1)
		return (-1);
	info->map = malloc(sizeof(int *) * (info->map_height));
	if(!info->map)
		return (-1);
	while(i < info->map_height)
	{
		info->map[i] = malloc(sizeof(int) * info->map_width);
		if (!info->map[i])
			return(free_partial_map(info, i, "Error\nMalloc failed\n"));
		j = 0;
		while(j < info->map_width)
		{
			if (j > ft_strlen(info->file_copy[i + info->pos_map_start]))
				c = ' ';
			else
				c = (info->file_copy)[i + info->pos_map_start][j];
			if (c == '\0' || c == ' ')
				info->map[i][j] = -1;
			else if (c == '0')
				info->map[i][j] = 0;
			else if (c == '1')
				info->map[i][j] = 1;
			else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (player_exist(info))
					return(free_partial_map(info, i, "Error\nMax 1 player\n"));
				info->
			}
		}
	}
}