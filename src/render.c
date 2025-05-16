#include "cub3d.h"

static void initialize_step_side(t_ray *ray, t_player *player)
{
    if (ray->dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos.x - ray->map.x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist_x;
    }
    if (ray->dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos.y - ray->map.y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map.y + 1.0 - player->pos.y) * ray->delta_dist_y;
    }
}

static void initialize_ray(t_ray *ray, t_player *player, int x)
{
    ray->hit = 0;
    ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
    ray->dir.x = player->dir.x + player->camera_plane.x * ray->camera_x;
    ray->dir.y = player->dir.y + player->camera_plane.y * ray->camera_x;
    ray->map = (t_point_int){(int)player->pos.x, (int)player->pos.y};
    ray->delta_dist_x = fabs(1 / ray->dir.x);
    ray->delta_dist_y = fabs(1 / ray->dir.y);
    initialize_step_side(ray, player);
}

int render_cub(t_info *info)
{
    (void)info;
    int x;

    x = 0;
    while (x < WINDOW_WIDTH)
    {
        initialize_ray(&info->ray, &info->player, x);
        dda(&info->ray, info);
        dda_continue(&info->ray, x, info);
        x++;
    }
    return (0);
}