/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:39:37 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/21 20:39:33 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_scene_identifier(const char *line)
{
	size_t	line_len;
	
	line_len = ft_strlen(line);
	return (
		ft_strnstr(line, "NO", line_len) != NULL
		|| ft_strnstr(line, "SO", line_len) != NULL
		|| ft_strnstr(line, "WE", line_len) != NULL
		|| ft_strnstr(line, "EA", line_len) != NULL);
}

static int	is_color_identifier(const char *line)
{
	size_t	line_len;
	
	line_len = ft_strlen(line);
	return (ft_strnstr(line, "C", line_len) != NULL
		|| ft_strnstr(line, "F", line_len) != NULL);
}

int	is_not_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	get_scene_elements(t_info *info)
{
	int	i;

	i = 0;
	while ((info->file_copy)[i] && info->element_count < 6)
	{
		if (is_scene_identifier((info->file_copy)[i]))
		{
			if (extract_scene_path(info, (info->file_copy)[i]) == -1)
				return (-1);
			info->element_count++;
		}
		else if (is_color_identifier((info->file_copy)[i]))
		{
			if (extract_color(info, (info->file_copy)[i]) == -1)
				return (-1);
			info->element_count++;
		}
		else if (is_not_empty_line((info->file_copy)[i]))
			return (-1);
		i++;
	}
	if (info->element_count < 6)
		return (-1);
	info->pos_last_element = i;
	return (0);
}
