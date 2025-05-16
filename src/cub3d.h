#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../mlx/mlx.h"

#include <stdlib.h> 

# define MAP_WIDTH 24 // example map width
# define MAP_HEIGHT 24 // example map hight

// # define TILE_SIZE 64

# define WINDOW_WIDTH 640 // example window width
# define WINDOW_HEIGHT 480 // example window height

typedef struct s_window
{
	int		x;
	int		y;
	void	*mlx_win;
}				t_window;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_player
{
	t_point		pos;		// position of the player
	t_point		dir;		// direction vector
	t_point		camera_plane;		// camera plane
}				t_player;

typedef struct s_ray
{
	t_point	    camera;
	t_point		dir;		// direction vector

}				t_ray;
typedef struct s_info
{
    int         **example_map; // random map for now

	void		*mlx;
	t_window	win;

	char		*map_name;		// map name from argument av[1]
	char		**map;          // real map
	int			map_width;      // real map width
	int			map_height;     // real map height
	char		direction;	// direction of the player
	
	t_player	player;
	t_ray		ray;

	double		time;
	double		old_time;
}			t_info;


// utils.c
void error(char *message, t_info *info);
int quit_program(t_info *info);
void free_example_map(t_info *info);

//initialize.c
void initialize_cub3d(t_info *info);
void initialize_example_map(t_info *info);

#endif