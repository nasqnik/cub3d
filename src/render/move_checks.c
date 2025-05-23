/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasqnik <nasqnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:33:37 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/23 21:05:06 by nasqnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_info *info, double x, double y)
{
	int		map_x;
	int		map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= info->map_height
		|| map_x < 0 || map_x >= info->map_width)
		return (1);
	return (info->map[map_y][map_x] == 1);
}

int	check_map_position(t_info *info, t_move *move)
{
	double	new_x;
	double	new_y;

	new_x = info->player.pos.x + move->step.x;
	new_y = info->player.pos.y + move->step.y;
	if (!is_wall(info, new_x + COL_BUFFER, info->player.pos.y + COL_BUFFER)
		&& !is_wall(info, new_x - COL_BUFFER, info->player.pos.y - COL_BUFFER)
		&& !is_wall(info, new_x + COL_BUFFER, info->player.pos.y - COL_BUFFER)
		&& !is_wall(info, new_x - COL_BUFFER, info->player.pos.y + COL_BUFFER))
	{
		info->player.pos.x = new_x;
	}
	if (!is_wall(info, info->player.pos.x + COL_BUFFER, new_y + COL_BUFFER)
		&& !is_wall(info, info->player.pos.x - COL_BUFFER, new_y - COL_BUFFER)
		&& !is_wall(info, info->player.pos.x + COL_BUFFER, new_y - COL_BUFFER)
		&& !is_wall(info, info->player.pos.x - COL_BUFFER, new_y + COL_BUFFER))
	{
		info->player.pos.y = new_y;
	}
	return (0);
}
