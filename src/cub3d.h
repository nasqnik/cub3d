#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../mlx/mlx.h"

#include <stdlib.h> 
#include <math.h>
#include <sys/time.h>
#include <stdio.h> // Delete before submission

# define MAP_WIDTH 24 // example map width
# define MAP_HEIGHT 24 // example map hight

// # define TILE_SIZE 64

# define WINDOW_WIDTH 640 // example window width
# define WINDOW_HEIGHT 480 // example window height
# define COL_BUFFER 0.15 		// collision buffer before the wall
# define SPEED_ROT 0.7

# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define RIGHT_ARROW 124
# define LEFT_ARROW 123

typedef enum s_direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
}			t_direction;

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

typedef struct s_move
{
    t_vector step;
	t_point_int new;
	t_point_int current;
	int map_cur_y_len;
	int map_new_y_len;
}				t_move;

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
	int				line_height;
	
}				t_ray;

typedef struct s_draw
{
	int			start;
	int			end;
	int			color;

}				t_draw;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			right;
	int			left;
}				t_keys;


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
	t_draw		draw;
	t_keys		keys;

	double		time;
	double		old_time;
	double		delta_time;

	double		move_speed;
	double		rot_speed;
}			t_info;


// utils.c
void error(char *message, t_info *info);
int quit_program(t_info *info);
void free_example_map(t_info *info);
double current_time(void);

// initialize.c
void initialize_cub3d(t_info *info);
void initialize_example_map(t_info *info);

// render.c
int render_cub3d(t_info *info);

// dda.c
void dda(t_ray *ray, t_info *info);
void dda_continue(t_ray *ray, t_info *info);

// move.c
void handle_movement(t_info *info);

// move_checks.c
int check_map_position(t_info *info, t_move *move);

// key.c
int key_press(int keycode, t_info *info);
int key_release(int keycode, t_info *info);

#endif