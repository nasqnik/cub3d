#include "../cub3d.h"

// static int check_collision_x(t_info *info, t_move *move)
// {
//     double	wall_dist_x;
// 	int		wall_cell_x;

//     if (move->step.x > 0)
// 	{
// 		wall_cell_x = (int)(move->new.x) + 1;
// 		wall_dist_x = wall_cell_x - move->new.x;
// 	}
//     else
//     {
//         wall_cell_x = (int)(move->new.x) - 1;
//         wall_dist_x = move->new.x - (wall_cell_x + 1);
//     }
//     if (wall_dist_x <= COL_BUFFER && info->map[move->current.y][wall_cell_x] == 1) // || info->map[move->current.y][wall_cell_x] != '1')
// 		return (1);
// 	return (0);
// }

// static int check_collision_y(t_info *info, t_move *move)
// {
//     double	wall_dist_y;
// 	int		wall_cell_y;

//     if (move->step.y > 0)
// 	{
// 		wall_cell_y = (int)(move->new.y) + 1;
// 		wall_dist_y = wall_cell_y - move->new.y;
// 	}
//     else
//     {
//         wall_cell_y = (int)(move->new.y) - 1;
//         wall_dist_y = move->new.y - (wall_cell_y + 1);
//     }
//     if ((wall_dist_y <= COL_BUFFER && info->map[wall_cell_y][move->current.x] == 1)) //|| info->map[wall_cell_y][move->current.x] != '1')
// 		return (1);
// 	return (0);
// }

// int check_map_boundaries(t_info *info, t_move *move)
// {
//     int	wall_ahead;
// 	int	wall_x;
// 	int	wall_y;

// 	if (move->new.y < 0.1 || move->new.y >= info->map_height - 0.1 || move->new.x < 0.1
// 		|| move->new.x >= move->map_new_y_len - 0.1) // can be changed to COL_BUFFER
// 		return (1);
// 	if (move->new.x < 0 || move->new.x >= move->map_new_y_len || move->current.x < 0
// 		|| move->current.x >= move->map_new_y_len)
// 		return (1);
// 	if (info->map[move->new.y][move->new.x] == -1      
// 		|| info->map[move->current.y][move->new.x] == -1
// 		|| info->map[move->new.y][move->current.x] == -1)
// 		return (1);
// 	wall_ahead = (info->map[move->new.y][move->new.x] == 1);   
// 	wall_x = (info->map[move->current.y][move->new.x] == 1);
// 	wall_y = (info->map[move->new.y][move->current.x] == 1);
// 	if (wall_ahead && (!wall_x && !wall_y))
// 		return (1);
// 	return (0);
// }


int check_map_position(t_info *info, t_move *move)
{
    if (move->new.y < 0 || move->new.y >= info->map_height || move->current.y < 0 || 
        move->current.y >= info->map_height) // >= or just >?
        return (1);
    // move->map_cur_y_len = ft_strlen(info->map[move->current.y]); // check with our map
    // move->map_new_y_len = ft_strlen(info->map[move->new.y]);     // check with our map

	move->map_cur_y_len = info->map_width;
	move->map_new_y_len = info->map_width; // it should be width, because it's the length of the row

    // if (check_map_boundaries(info, move))
    //     return (1);
    if (info->map[move->current.y][move->new.x] != 1 ) //&& !check_collision_x(info, move)
		info->player.pos.x += move->step.x;
    if (info->map[move->new.y][move->current.x] != 1 ) //&& !check_collision_y(info, move)
		info->player.pos.y += move->step.y;

    return (0);
}