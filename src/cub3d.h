#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include "../mlx/mlx.h"
# include <fcntl.h>

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

typedef struct s_info
{
    int         example_map; // random map for now

	void		*mlx;
	t_window	win;
	char		*map_name;		// map name from argument av[1]
	int			row_count;
	int			line_max_length;
	char		**file_copy;          // local copy
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	int			*F_color;
	int			map_width;      // real map width
	int			map_height;     // real map height
}			t_info;


// utils.c
void error(char *message, t_info *info);
int quit_program(t_info *info);

#endif