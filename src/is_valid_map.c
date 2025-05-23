/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:49:07 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/23 20:41:52 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	free_partial_visited(int **visited, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (visited[i])
			free(visited[i]);
		visited[i] = NULL;
		i++;
	}
	free(visited);
	visited = NULL;
	return (-1);
}

static int	flood_fill(t_info *info, int **visited, int x, int y)
{
	if (x < 0 || y < 0 || y >= info->map_height || x >= info->map_width)
		return (-1);
	if (visited[y][x] || info->map[y][x] == 1)
		return (0);
	if (info->map[y][x] == -1)
		return (-1);
	visited[y][x] = 1;
	if (flood_fill(info, visited, x + 1, y) == -1
		|| flood_fill(info, visited, x - 1, y) == -1
		|| flood_fill(info, visited, x, y + 1) == -1
		|| flood_fill(info, visited, x, y - 1) == -1)
		return (-1);
	return (0);
}
int	is_map_enclosed(int **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 0)
			{
				if (y - 1 < 0 || map[y - 1][x] == -1)
					return (0);
				if (y + 1 >= height || map[y + 1][x] == -1)
					return (0);
				if (x - 1 < 0 || map[y][x - 1] == -1)
					return (0);
				if (x + 1 >= width || map[y][x + 1] == -1)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
int	is_valid_map(t_info *info)
{
	int	**visited;
	int	y;

	visited = malloc(sizeof(int *) * info->map_height);
	if (!visited)
		return (-1);
	y = 0;
	while (y < info->map_height)
	{
		visited[y] = ft_calloc(info->map_width, sizeof(int));
		if (!visited[y])
			return (free_partial_visited(visited, y));
		y++;
	}
	if (flood_fill(info, visited, info->player.pos.x, info->player.pos.y) == -1)
	{
		ft_error("Error\nMap is not closed\n");
		return (free_partial_visited(visited, y));
	}
	free_partial_visited(visited, y);
	if (!is_map_enclosed(info->map, info->map_width, info->map_height))
		return (ft_error("Error\nMap is not closed\n"));
	return (0);
}
