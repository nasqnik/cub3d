/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:38:47 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/16 20:42:42 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_color(int **dest, const char *line)
{
	char	**rgb;
	int		i;

	i = 0;
	if (*dest != NULL)
		return (-1);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (-1);
	while (rgb[i])
		i++;
	if (i != 3)
	{
		free_split(rgb);
		return (ft_error("Error\nColor must have 3 components\n"));
	}
	*dest = malloc(sizeof(int) * 3);
	if (!*dest)
	{
		free_split(rgb);
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		(*dest)[i] = ft_atoi(rgb[i]);
		if ((*dest)[i] < 0 || (*dest)[i] > 255)
		{
			free(*dest);
			*dest = NULL;
			free_split(rgb);
			return(ft_error("Error\nColor values must be between 0 & 255\n"));
		}
		i++;
	}
	free_split(rgb);
	return (0);
}

int	extract_color(t_info *info, char *line)
{
	if (ft_strnstr(line, "F", 1))
		return parse_color(&(info->F_color), line + 1);
	if (ft_strnstr(line, "C", 1))
		return parse_color(&(info->C_color), line + 1);
	return (-1);
}