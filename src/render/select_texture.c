/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:19:33 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/22 21:20:26 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	*select_texture(t_info *info, t_ray *ray)
{
	int	tex_index;

	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			tex_index = WE;
		else
			tex_index = EA;
	}
	else
	{
		if (ray->dir.y > 0)
			tex_index = NO;
		else
			tex_index = SO;
	}
	return (&info->textures[tex_index]);
}

int	calculate_tex_x(t_ray *ray, t_texture *tex, t_info *info)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = info->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = info->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->img_width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = tex->img_width - tex_x - 1;
	return (tex_x);
}

void	draw_ceiling(t_info *info, int x, int y_start, int y_end)
{
	int	color;
	int	y;

	color = (info->c_color[0] << 16)
		| (info->c_color[1] << 8)
		| info->c_color[2];
	y = y_start;
	while (y < y_end)
	{
		((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
		y++;
	}
}

void	draw_wall(t_info *info, int x, t_texture *tex, int tex_x)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;
	t_ray	*ray;

	y = info->draw.start;
	ray = &info->ray;
	while (y < info->draw.end)
	{
		d = y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * tex->img_height) / ray->line_height) / 256;
		color = tex->data[tex->img_width * tex_y + tex_x];
		((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
		y++;
	}
}

void	draw_floor(t_info *info, int x, int y_start, int y_end)
{
	int	color;
	int	y;

	color = (info->f_color[0] << 16)
		| (info->f_color[1] << 8)
		| info->f_color[2];
	y = y_start;
	while (y < y_end)
	{
		((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
		y++;
	}
}
