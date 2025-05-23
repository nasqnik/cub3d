/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasqnik <nasqnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:15:31 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/23 19:59:51 by nasqnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_step_side(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos.x - ray->map.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x
			= (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos.y - ray->map.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y
			= (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist_y;
	}
}

static void	initialize_ray(t_ray *ray, t_player *player, int x)
{
	ray->hit = 0;
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir.x = player->dir.x + player->camera.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->camera.y * ray->camera_x;
	ray->map = (t_point_int){(int)player->pos.x, (int)player->pos.y};
	if (ray->dir.x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir.y);
	initialize_step_side(ray, player);
}

void	update_time_speed(t_info *info)
{
	info->old_time = info->time;
	info->time = current_time();
	info->delta_time = (info->time - info->old_time) / 1000.0;
	info->move_speed = info->delta_time * 60.0;
	info->rot_speed = info->delta_time * 3.0;
}

void	render_column(t_info *info, int x)
{
	int			y;
	t_ray		*ray;
	t_texture	*tex;
	int			tex_x;

	ray = &info->ray;
	initialize_ray(ray, &info->player, x);
	dda(ray, info);
	dda_continue(ray, info);
	tex = select_texture(info, ray);
	tex_x = calculate_tex_x(ray, tex, info);
	y = 0;
	draw_ceiling(info, x, y, info->draw.start);
	draw_wall(info, x, tex, tex_x);
	draw_floor(info, x, info->draw.end, WINDOW_HEIGHT);
}

int	render_cub3d(t_info *info)
{
	int	x;

	update_time_speed(info);
	handle_movement(info);
	ft_memset(info->_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		render_column(info, x);
		x++;
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->_img, 0, 0);
	return (0);
}
