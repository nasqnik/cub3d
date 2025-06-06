/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasqnik <nasqnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:29:58 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/26 12:16:20 by nasqnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda(t_ray *ray, t_info *info)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map.y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map.x < 0 || ray->map.y < 0 || ray->map.y >= info->map_height
			|| ray->map.x >= info->map_width)
		{
			ray->hit = 1;
			break ;
		}
		if (info->map[ray->map.y][ray->map.x] > 0)
			ray->hit = 1;
	}
}

void	dda_continue(t_ray *ray, t_info *info)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist <= 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > WINDOW_HEIGHT * 10)
		ray->line_height = WINDOW_HEIGHT * 10;
	info->draw.start = ray->line_height * (-1) / 2 + WINDOW_HEIGHT / 2;
	if (info->draw.start < 0)
		info->draw.start = 0;
	info->draw.end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (info->draw.end >= WINDOW_HEIGHT)
		info->draw.end = WINDOW_HEIGHT - 1;
}
