/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:37:47 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/18 22:05:36 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_texture(char **dest, const char *line)
{
	int		fd;
	char	*trimmed_line;

	fd = 0;
	if (*dest != NULL)
		return (-1);
	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
		return (-1);
	*dest = ft_strdup(trimmed_line);
	free(trimmed_line);
	if (!*dest)
		return (-1);
	fd = open (*dest, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nTexture file not found\n"));
	close (fd);
	return (0);
}

int	extract_scene_path(t_info *info, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (parse_texture(&info->no_path, line + 2));
	if (ft_strnstr(line, "SO", 2))
		return (parse_texture(&info->so_path, line + 2));
	if (ft_strnstr(line, "WE", 2))
		return (parse_texture(&info->we_path, line + 2));
	if (ft_strnstr(line, "EA", 2))
		return (parse_texture(&info->ea_path, line + 2));
	return (-1);
}
