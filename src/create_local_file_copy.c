/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_local_file_copy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:41:06 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/18 19:58:11 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_file_rows(t_info *info, char *file_name)
{
	char *tmp_line;
	int	fd;

	info->row_count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nCould not open file\n"));
	tmp_line = get_next_line(fd);
	while (tmp_line)
	{
		info->row_count++;
		free(tmp_line);
		tmp_line = get_next_line(fd);
	}
	close(fd);
	if (info->row_count == 0)
		return (-1);
	return (0);
}

static int	free_file_partial(char **file, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (file[i])
			free(file[i]);
		i++;
	}
	free(file);
	return (-1);
}

int	create_local_file_copy(t_info *info, char *file_name)
{
	char 	*tmp_line;
	int		i;
	int		fd;

	if (get_file_rows(info, file_name) == -1)
		return (-1);
	i = 0;	
	info->file_copy = malloc(sizeof(char *) * (info->row_count + 1));
	if (!(info->file_copy))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nCould not open map\n"));
	tmp_line = get_next_line(fd);
	if (!tmp_line)
		return (-1);
	while (tmp_line && i < info->row_count)
	{
		(info->file_copy)[i] = tmp_line;
		i++;
		tmp_line = get_next_line(fd);
	}
	(info->file_copy)[i] = NULL;
	close (fd);
	if (i < info->row_count)
		return (free_file_partial(info->file_copy, i));
	return (0);
}
