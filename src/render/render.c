#include "../cub3d.h"

#define NO 0
#define SO 1
#define EA 2
#define WE 3

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

void update_time_speed(t_info *info)
{
    info->old_time = info->time;
    info->time = current_time();
    info->delta_time = (info->time - info->old_time) / 1000.0;
    info->move_speed = info->delta_time * 30.0;
    info->rot_speed = info->delta_time * 3.0;
}
int render_cub3d(t_info *info)
{
    int x;

    update_time_speed(info);
    handle_movement(info);

    // Clear the image buffer
    ft_memset(info->_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(int));

    x = 0;
    while (x < WINDOW_WIDTH)
    {
        initialize_ray(&info->ray, &info->player, x);
        dda(&info->ray, info);
        dda_continue(&info->ray, info);

        int y = info->draw.start;
        t_ray *ray = &info->ray;

        // 1. Choose wall texture
        int tex_index;
        if (ray->side == 0)
            tex_index = (ray->dir.x > 0) ? WE : EA;
        else
            tex_index = (ray->dir.y > 0) ? NO : SO;
        t_texture *tex = &info->textures[tex_index];

        // 2. Calculate where the wall was hit
        double wall_x;
        if (ray->side == 0)
            wall_x = info->player.pos.y + ray->perp_wall_dist * ray->dir.y;
        else
            wall_x = info->player.pos.x + ray->perp_wall_dist * ray->dir.x;
        wall_x -= floor(wall_x);

        // 3. Texture X coordinate
        int tex_x = (int)(wall_x * (double)tex->img_width);
        if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1 && ray->dir.y < 0))
            tex_x = tex->img_width - tex_x - 1;

        // Draw ceiling
        y = 0;
        while (y < info->draw.start)
        {
            int color = info->c_color[0] << 16 | info->c_color[1] << 8 | info->c_color[2];
            ((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
            y++;
        }

        // Draw wall
        while (y < info->draw.end)
        {
            int d = y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128;
            int tex_y = ((d * tex->img_height) / ray->line_height) / 256;

            int color = tex->data[tex->img_height * tex_y + tex_x];
            ((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
            y++;
        }

        // Draw floor
        while (y < WINDOW_HEIGHT)
        {
            int color = info->f_color[0] << 16 | info->f_color[1] << 8 | info->f_color[2];
            ((int *)info->_addr)[y * WINDOW_WIDTH + x] = color;
            y++;
        }

        x++;
    }

    mlx_put_image_to_window(info->mlx, info->mlx_win, info->_img, 0, 0);
    return (0);
}
