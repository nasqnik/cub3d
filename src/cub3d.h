/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasqnik <nasqnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:02:27 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/21 09:27:40 by nasqnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# if __APPLE__
# include "../mlx/mlx.h"
# elif __linux__
#  include "../mlx_linux/mlx.h"
# endif


# include <fcntl.h>
# include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <sys/time.h>

# define MAP_WIDTH 24 		// example map width
# define MAP_HEIGHT 24 		// example map hight

// # define TILE_SIZE 64

# define WINDOW_WIDTH 640 	// example window width
# define WINDOW_HEIGHT 480 	// example window height
# define COL_BUFFER 0.01 	// collision buffer before the wall
# define SPEED_ROT 0.7

# if __APPLE__
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# elif __linux__
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define RIGHT_ARROW 65363
#  define LEFT_ARROW 65361
# endif

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
	char			direction;	// direction of the player
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
	void		*mlx;
	void		*mlx_win;
	
	int			row_count;
	int 		**map;			//malloc'd
	char		*map_name;		// map name from argument av[1]
	
	int			map_width;		// real map width
	int			map_height;		// real map height <--- update to row_count

	t_player	player;
	
	
	t_ray		ray;
	t_draw		draw;
	t_keys		keys;
	
	char		**file_copy;	// local copy - malloc'd
	char		*no_path;		//malloc'd
	char		*so_path;		//malloc'd
	char		*we_path;		//malloc'd
	char		*ea_path;		//malloc'd
	
	int			*f_color;		//malloc'd
	int			*c_color;		//malloc'd
	
	int			element_count;
	int			pos_last_element;
	int			pos_map_start;

	double		time;
	double		old_time;
	double		delta_time;

	double		move_speed;
	double		rot_speed;
}			t_info;

// check_lines_before_map.c
int		check_lines_before_map(t_info *info);

// convert_to_map.c
int		convert_to_map(t_info *info);

// create_local_file_copy.c
int		create_local_file_copy(t_info *info, char *file_name);

// extract_color.c
int		extract_color(t_info *info, char *line);

// extract_scene_path.c
int		extract_scene_path(t_info *info, char *line);

// get_scene_elements.c
int		is_not_empty_line(const char *line);
int		get_scene_elements(t_info *info);

// is_valid_map.c
int		is_valid_map(t_info *info);

// utils.c
int		ft_error(const char *message);
int		ft_free_file(const char *message, t_info *info);
void	free_split(char **array);


// ana's files


// utils.c
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