/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasqnik <nasqnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:02:27 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/26 11:38:15 by nasqnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# if __APPLE__
#  include "../mlx/mlx.h"
# elif __linux__
#  include "../mlx_linux/mlx.h"
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h> 
# include <math.h>
# include <sys/time.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define IMAGE_WIDTH 64
# define IMAGE_HEIGHT 64

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define COL_BUFFER 0.1
# define SPEED_ROT 0.7
# define SPEED_MOVE 2.0

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# if __APPLE__
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define RIGHT_ARROW 124
#  define LEFT_ARROW 123
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
	t_point_double	pos;
	t_vector		dir;
	t_vector		camera;
	char			direction;
}				t_player;

typedef struct s_move
{
	t_vector	step;
	t_point_int	new;
	t_point_int	current;
	int			map_cur_y_len;
	int			map_new_y_len;
}				t_move;

typedef struct s_ray
{
	int				hit;			
	double			camera_x;
	t_vector		dir;			
	t_point_int		map;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
}				t_ray;

typedef struct s_draw
{
	double			start;
	double			end;
	int				color;

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

typedef struct s_texture
{
	void	*tex;
	int		img_width;
	int		img_height;
	int		*data;
}				t_texture;

typedef struct s_info
{
	void		*mlx;
	void		*mlx_win;

	int			row_count;
	int			**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
	t_keys		keys;
	t_texture	textures[4];

	char		**file_copy;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			*f_color;
	int			*c_color;
	int			element_count;
	int			pos_last_element;
	int			pos_map_start;

	double		time;
	double		old_time;
	double		delta_time;

	void		*_img;
	char		*_addr;
}			t_info;

// check_lines_before_map.c
int			check_lines_before_map(t_info *info);

// convert_to_map.c
int			convert_to_map(t_info *info);

// create_local_file_copy.c
int			create_local_file_copy(t_info *info, char *file_name);

// extract_color.c
int			extract_color(t_info *info, char *line);

// extract_scene_path.c
int			extract_scene_path(t_info *info, char *line);

// get_scene_elements.c
int			is_not_empty_line(const char *line);
int			get_scene_elements(t_info *info);

// is_valid_map.c
int			is_valid_map(t_info *info);

// utils.c
int			ft_error(const char *message);
int			ft_free_file(const char *message, t_info *info);
void		free_split(char **array);

// render files

// dda.c
void		dda(t_ray *ray, t_info *info);
void		dda_continue(t_ray *ray, t_info *info);

// initialize.c
void		initialize_cub3d(t_info *info);

// move.c
void		handle_movement(t_info *info);

// move_checks.c
int			check_map_position(t_info *info, t_move *move);

// key.c
int			key_press(int keycode, t_info *info);
int			key_release(int keycode, t_info *info);

// render.c
int			render_cub3d(t_info *info);

// select_texture.c
t_texture	*select_texture(t_info *info, t_ray *ray);
int			calculate_tex_x(t_ray *ray, t_texture *tex, t_info *info);
void		draw_ceiling(t_info *info, int x, int y_start, int y_end);
void		draw_wall(t_info *info, int x, t_texture *tex, int tex_x);
void		draw_floor(t_info *info, int x, int y_start, int y_end);

// textures.c
void		destroy_textures(t_info *info);
void		load_textures(t_info *info);
void		initialize_textures(t_info *info);

// utils.c
int			quit_program(t_info *info);
int			quit_program_message(char *message, t_info *info);
double		current_time(void);

#endif