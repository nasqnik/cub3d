/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:51:58 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/18 20:48:18 by saherrer         ###   ########.fr       */
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
		if ((int)ft_strlen(file[i]) > max_length)
			max_length = ft_strlen(file[i]);
		i++;
	}
	return (max_length);
}

static int	free_partial_map(t_info *info, int count, const char *message)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (info->map[i])
			free(info->map[i]);
		i++;
	}
	free(info->map);
	info->map = NULL;
	return (ft_error(message));
}

static int	define_player_pos(t_info *info, int j, int i, char c)
{
	if (info->player.x != -1)
		return(free_partial_map(info, i + 1, "Error\nMax 1 player\n"));
	info->player.x = j;
	info->player.y = i;
	info->player.dir = c;
	info->map[i][j] = 0;
	return (0);
}

static int	process_map(t_info *info, int i, int j)
{
	char c;
	
	while(j < info->map_width)
	{
		if (j > (int)ft_strlen(info->file_copy[i + info->pos_map_start]))
			c = ' ';
		else
			c = (info->file_copy)[i + info->pos_map_start][j];
		if (c == '\0' || c == ' ' || c == '\n')
			info->map[i][j] = -1;
		else if (c == '0')
			info->map[i][j] = 0;
		else if (c == '1')
			info->map[i][j] = 1;
		else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		{
			if(define_player_pos(info, j, i ,c) == -1)
				return (-1);
		}
		else
			return(free_partial_map(info, i + 1, "Error\nInvalid map char\n"));
		j++;
	}
	return (0);
}

int	convert_to_map(t_info *info)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	info->map_width = find_max_line_length(info->file_copy + info->pos_map_start);
	info->map_height = info->row_count - info->pos_map_start;
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
		if (process_map(info, i, j) == -1)
			return (-1);
		i++;
	}
	if (info->player.x == -1)
		return (free_partial_map(info, i, "Error\nNo player found\n"));
	return (0);
}
