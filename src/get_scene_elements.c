/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:39:37 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/16 21:07:40 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*is_scene_identifier(const char *line)
{
	return (ft_strnstr(line, "NO", 2)
		|| ft_strnstr(line, "SO", 2)
		|| ft_strnstr(line, "WE", 2)
		|| ft_strnstr(line, "EA", 2));
}

static char	*is_color_identifier(const char *line)
{
	return (ft_strnstr(line, "C", 1)
		|| ft_strnstr(line, "F", 1));
}

int	get_scene_elements(t_info *info)
{
	int	i;

	i = 0;
	while((info->file_copy)[i] && info->element_count < 6)
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
}