/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:38:47 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/23 19:38:27 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_commas(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

static int	is_valid_rgb_component(const char *str)
{
	int	value;

	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (!*str)
		return (0);
	if (*str < '0' || *str > '9')
		return (0);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (0);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str)
		return (0);
	return (1);
}

static int	validate_and_convert_rgb(int **dest, char **rgb)
{
	int	i;

	i = 0;
	*dest = malloc(sizeof(int) * 3);
	if (!*dest)
	{
		free_split(rgb);
		return (-1);
	}
	while (i < 3)
	{
		if (!rgb[i] || !is_valid_rgb_component(rgb[i]))
		{
			free(*dest);
			*dest = NULL;
			free_split(rgb);
			return (ft_error("Error\nInvalid RGB component\n"));
		}
		(*dest)[i] = ft_atoi(rgb[i]);
		i++;
	}
	return (0);
}

static int	parse_color(int **dest, const char *line)
{
	char	**rgb;
	char	*trimmed_line;

	if (*dest != NULL)
		return (-1);
	if (count_commas(line) != 2)
		return (ft_error("Error\nColor must have exactly 3 components\n"));
	trimmed_line = ft_strtrim(line, " \n\t");
	if (!trimmed_line)
		return (-1);
	rgb = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (!rgb)
		return (-1);
	if (validate_and_convert_rgb(dest, rgb) == -1)
		return (-1);
	free_split(rgb);
	return (0);
}

int	extract_color(t_info *info, char *line)
{
	char	*new_line;

	new_line = ft_strnstr(line, "F", ft_strlen(line));
	if (new_line)
		return (parse_color(&(info->f_color), new_line + 1));
	new_line = ft_strnstr(line, "C", ft_strlen(line));
	if (new_line)
		return (parse_color(&(info->c_color), new_line + 1));
	return (-1);
}
