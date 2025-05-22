/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:33:28 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/22 22:24:35 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	rotate_player(t_info *info, t_player *player, t_direction direction)
{
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	if (direction == ROTATE_RIGHT)
		rotation = SPEED_ROT * info->delta_time;
	else
		rotation = -SPEED_ROT * info->delta_time;
	if (fabs(rotation) > 0.1)
	{
		if (rotation > 0)
			rotation = 0.1;
		else
			rotation = -0.1;
	}
	cos_rot = cos(rotation);
	sin_rot = sin(rotation);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos_rot - player->dir.y * sin_rot;
	player->dir.y = old_dir_x * sin_rot + player->dir.y * cos_rot;
	old_plane_x = player->camera_plane.x;
	player->camera_plane.x = player->camera_plane.x * cos_rot - player->camera_plane.y * sin_rot;
	player->camera_plane.y = old_plane_x * sin_rot + player->camera_plane.y * cos_rot;
}

static void	calculate_movement(t_info *info, t_move *move, t_direction direction)
{
	if (direction == FORWARD)
	{
		move->step.x = info->player.dir.x * (info->move_speed * info->delta_time);
		move->step.y = info->player.dir.y * (info->move_speed * info->delta_time);
	}
	else if (direction == BACKWARD)
	{
		move->step.x = -info->player.dir.x * (info->move_speed * info->delta_time);
		move->step.y = -info->player.dir.y * (info->move_speed * info->delta_time);
	}
	else if (direction == LEFT)
	{
		move->step.x = -info->player.camera_plane.x * (info->move_speed * info->delta_time);
		move->step.y = -info->player.camera_plane.y * (info->move_speed * info->delta_time);
	}
	else if (direction == RIGHT)
	{
		move->step.x = info->player.camera_plane.x * (info->move_speed * info->delta_time);
		move->step.y = info->player.camera_plane.y * (info->move_speed * info->delta_time);
	}
}
static void	update_position(t_info *info)
{
	static t_point_double	prev = (t_point_double){-1, -1};
	t_point_double			delta;
	double					distance;

	if (prev.x == -1)
	{
		prev.x = info->player.pos.x;
		prev.y = info->player.pos.y;
	}
	delta.x = info->player.pos.x - prev.x;
	delta.y = info->player.pos.y - prev.y;
	distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance > 0.2)
	{
		info->player.pos.x = prev.x;
		info->player.pos.y = prev.y;
	}
	else
	{
		prev.x = info->player.pos.x;
		prev.y = info->player.pos.y;
	}
}

static void	apply_movement(t_info *info, t_move *move)
{
	double new_x;
	double new_y;

	new_x = info->player.pos.x + move->step.x;
	new_y = info->player.pos.y + move->step.y;
	move->new.x = (int)new_x;
	move->new.y = (int)new_y;
	move->current.x = info->player.pos.x;
	move->current.y = info->player.pos.y;
	if (check_map_position(info, move))
		return ;
	update_position(info);
}

void	handle_movement(t_info *info)
{
	t_move move;
	int direction;

	ft_bzero(&move, sizeof(t_move));
	direction = -1;
	if (info->keys.w)
		direction = FORWARD;
	else if (info->keys.s)
		direction = BACKWARD;
	else if (info->keys.a)
		direction = LEFT;
	else if (info->keys.d)
		direction = RIGHT;
	else if (info->keys.right)
		direction = ROTATE_RIGHT;
	else if (info->keys.left)
		direction = ROTATE_LEFT;
	if (direction != -1 && direction != ROTATE_LEFT && direction != ROTATE_RIGHT)
	{
		calculate_movement(info, &move, direction);
		apply_movement(info, &move);
	}
	else if (direction == ROTATE_LEFT || direction == ROTATE_RIGHT)
		rotate_player(info, &info->player, direction);
}
