#include "cub3d.h"

void initialize_player(t_info *info)
{
    if (info->direction == 'N')
    {
        info->player.dir = (t_point){0.0, -1.0};
        info->player.camera_plane = (t_point){0.66, 0.0};
    }
    else if (info->direction == 'S')
    {
        info->player.dir = (t_point){0.0, 1.0};
        info->player.camera_plane = (t_point){-0.66, 0.0};
    }
    else if (info->direction == 'E')
    {
        info->player.dir = (t_point){1.0, 0.0};
        info->player.camera_plane = (t_point){0.0, 0.66};
    }
    else if (info->direction == 'W')
    {
        info->player.dir = (t_point){-1.0, 0.0};
        info->player.camera_plane = (t_point){0.0, -0.66};
    }
}


void initialize_cub3d(t_info *info)
{
    info->time = 0.0;
    info->old_time = 0.0;
    info->player.pos = (t_point){22, 12};    // change after parsing
    info->direction = 'W';                   // change after parsing
    initialize_player(info);
}


// Delete after completed parsing

int random_map[MAP_WIDTH][MAP_HEIGHT]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void initialize_example_map(t_info *info)
{
    int i, j;

    info->map = NULL;                   // real map   
    info->map_width = MAP_WIDTH;        // change after parsing
    info->map_height = MAP_HEIGHT;      // change after parsing
    

    // Delete after completed parsing
    info->example_map = (int **)malloc(MAP_WIDTH * sizeof(int *));
    if (!info->example_map)
        error("Memory allocation failed for example_map", info);
    for (i = 0; i < MAP_WIDTH; i++) {
        info->example_map[i] = (int *)malloc(MAP_HEIGHT * sizeof(int));
        if (!info->example_map[i])
            error("Memory allocation failed for example_map row", info);
        for (j = 0; j < MAP_HEIGHT; j++) {
            info->example_map[i][j] = random_map[i][j];
        }
    }
    //--------------------------------//

}

void free_example_map(t_info *info)
{
    int i;

    if (info->example_map) {
        for (i = 0; i < MAP_WIDTH; i++) {
            free(info->example_map[i]);
        }
        free(info->example_map);
        info->example_map = NULL;
    }
}