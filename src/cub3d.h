/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:02:27 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/18 22:07:08 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>

# define MAP_WIDTH 8 // example map width
# define MAP_HEIGHT 8 // example map hight

// # define TILE_SIZE 64

# define WINDOW_WIDTH 640 // example window width
# define WINDOW_HEIGHT 480 // example window height

typedef struct s_window
{
	int		x;
	int		y;
	void	*mlx_win;
}				t_window;

// typedef struct s_point
// {
// 	int		x;
// 	int		y;
// }				t_point;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_info
{
	void		*mlx;
	t_window	win;
	int			row_count;
	int			**map;			//malloc'd
	int			map_width;		// real map width
	int			map_height;		// real map height
	t_player	player;
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
// void	error(char *message, t_info *info);
// int		quit_program(t_info *info);

#endif