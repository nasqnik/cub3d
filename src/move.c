#include "cub3d.h"

void calculate_movement(t_info *info, t_move *move, t_direction direction)
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
void update_position(t_info *info)
{
    static t_point_double   prev = (t_point_double){-1, -1};
    t_point_double          delta;
    double                  distance;

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


void apply_movement(t_info *info, t_move *move)
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

void handle_movement(t_info *info)
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
    if (direction != -1)
    {
        calculate_movement(info, &move, direction);
        apply_movement(info, &move);
    }
}