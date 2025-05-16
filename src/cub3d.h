#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../mlx/mlx.h"

#include <stdlib.h> 
#include <math.h>
#include <stdio.h> // Delete before submission

# define MAP_WIDTH 24 // example map width
# define MAP_HEIGHT 24 // example map hight

// # define TILE_SIZE 64

# define WINDOW_WIDTH 640 // example window width
# define WINDOW_HEIGHT 480 // example window height



typedef struct s_point_double
{
	double		x;
	double		y;
}				t_point_double;

typedef struct s_point_int
{
	int			x;
	int			y;
}				t_point_int;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	t_point_double	pos;				// position of the player
	t_vector		dir;				// direction vector
	t_vector		camera_plane;
}				t_player;

typedef struct s_ray
{
	int				hit;			// did the ray hit a wall?
	double	    	camera_x;
	t_vector		dir;			// direction vector
	t_point_int		map;			// which box of the map we're in
	double			side_dist_x; 	// length of ray from current position to next x or y-side
	double			side_dist_y;
	double			delta_dist_x; 	// length of ray from one x or y-side to next x or y-side
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;		    // what direction to step in x or y-direction (either +1 or -1)
	int				step_y;
	int				side;			// If an x-side was hit, side is set to 0, if an y-side was hit, side will be 1
	
}				t_ray;

typedef struct s_info
{
    int         **example_map; // random map for now

	void		*mlx;
	void		*mlx_win;

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

// initialize.c
void initialize_cub3d(t_info *info);
void initialize_example_map(t_info *info);

// render.c
int render_cub(t_info *info);

#endif