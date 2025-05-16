#include "cub3d.h"
#include <stdio.h>

// int random_map[MAP_WIDTH][MAP_HEIGHT]=
// {
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

void initialize_mlx(t_info *info)
{
	info->mlx = mlx_init();

	info->win.x = WINDOW_WIDTH;	 // example window width, change after parsing
	info->win.y = WINDOW_HEIGHT;	// example window height, change after parsing

	if (!info->mlx)
		error("mlx_init failed in initialize_mlx", info);
	info->win.mlx_win = mlx_new_window(info->mlx,
			info->win.x, info->win.y, "cub3D");
	if (!info->win.mlx_win)
		error("mlx_new_window failed in initialize_mlx", info);
}

// void initialize_map(t_info *info)
// {
//	 info->map = NULL;                   // real map   

//     // info->example_map = random_map;     // example map

//     info->map_width = MAP_WIDTH;        // change after parsing
//     info->map_height = MAP_HEIGHT;      // change after parsing
// }

int	check_file_name(char *file_name)
{
	int	i;
	int	name_length;

	i = 0;
	name_length = ft_strlen(file_name);
	if(name_length < 5)
		return (-1);
	if((file_name[name_length - 4] == '.' ) &&
		(file_name[name_length - 3] == 'c' ) &&
		(file_name[name_length - 2] == 'u' ) &&
		(file_name[name_length - 1] == 'b'))
		return (1);
	return (-1);
}

static int	get_map_rows_and_length(t_info *info, char *file_name)
{
	char *tmp_line;
	int	fd;

	info->row_count = 0;
	info->line_max_length = -1;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nCould not open map\n"));
	tmp_line = get_next_line(fd);
	if (!tmp_line)
		return (-1);
	while (tmp_line)
	{
		if (ft_strlen(tmp_line) > info->line_max_length)
			info->line_max_length = ft_strlen(tmp_line);
		info->row_count++;
		free(tmp_line);
		tmp_line = get_next_line(fd);
	}
	close(fd);
	if (info->row_count = 0 || info->line_max_length < 1)
		return (-1);
	return (0);
}

static int	free_map_partial(char **map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
	return (-1);
}

int	create_local_file_copy(t_info *info, char *file_name)
{
	char 	*tmp_line;
	int		i;
	int		fd;

	if (get_map_rows_and_length(info, file_name) == -1)
		return (-1);
	i = 0;	
	info->file_copy = malloc(sizeof(char *) * (info->row_count + 1));
	if (!(info->file_copy))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nCould not open map\n"));
	tmp_line = get_next_line(fd);
	if (!tmp_line)
		return (-1);
	while (tmp_line && i < info->row_count)
	{
		(info->file_copy)[i] = tmp_line;
		i++;
		tmp_line = get_next_line(fd);
	}
	(info->file_copy)[i] = NULL;
	close (fd);
	if (i < info->row_count)
		return (free_map_partial(info->file_copy, i));
	return (0);
}

char	*is_scene_identifier(const char *line)
{
	return (ft_strnstr(line, "NO", 2)
		|| ft_strnstr(line, "SO", 2)
		|| ft_strnstr(line, "WE", 2)
		|| ft_strnstr(line, "EA", 2));
}

char	*is_color_identifier(const char *line)
{
	return (ft_strnstr(line, "C", 1)
		|| ft_strnstr(line, "F", 1));
}
int	parse_texture(char **dest, const char *line)
{
	int	fd;

	fd = 0;
	if (*dest != NULL)
		return (-1);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*dest = ft_strdup(line);
	if(!*dest)
		return (-1);
	fd = open (*dest, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error\nTexture file not found\n"));
	close (fd);
	return (0);
}

int	extract_scene_path(t_info *info, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (parse_texture(&info->NO_path, line + 2));
	if (ft_strnstr(line, "SO", 2))
		return (parse_texture(&info->SO_path, line + 2));
	if (ft_strnstr(line, "WE", 2))
		return (parse_texture(&info->WE_path, line + 2));
	if (ft_strnstr(line, "EA", 2))
		return (parse_texture(&info->EA_path, line + 2));
	return (-1);
}

int	extract_color(t_info *info, char *line)
{
	if (ft_strnstr(line, "F", 1))
		return parse_color(&(info->F_color), line + 1);
	if (ft_strnstr(line, "C", 1))
		return parse_color(&(info->C_color), line + 1);
	return (-1);
}

int	get_scene_elements(t_info *info, char *file_name)
{
	int	i;

	i = 0;
	while((info->file_copy)[i] && info->element_count < 6)
	{
		if (is_scene_identifier((info->file_copy)[i]))
		{
			if (extract_scene_path(info, (info->file_copy)[i]) == -1)
				return (-1);
			info->element_count++;
		}
		else if (is_color_identifier((info->file_copy)[i]))
		{
			if (extract_color(info, (info->file_copy)[i]) == -1)
				return (-1);
			info->element_count++;
		}
		else if (is_not_empty_line((info->file_copy)[i]))
			return (-1);
		i++;
	}
}

int	file_parsing(t_info *info, char *file_name)
{
	if (check_file_name(file_name) == -1)
		return(ft_error("Error\nIncorrect file extension\n"));
	if (create_local_file_copy(info, file_name) == -1)
		return(ft_error("Error\nCould not create local file copy\n"));
	if (get_scene_elements(info, file_name) == -1)
		return(ft_error("Error\nIncorrect scene elements\n")); // need to free items after this point
}

void	init_file_info(t_info *info)
{
	info->file_copy = NULL;
	info->NO_path = NULL;
	info->SO_path = NULL;
	info->WE_path = NULL;
	info->EA_path = NULL;
	info->F_color = NULL;
	info->C_color = NULL;
	info->element_count < 6;
}

int main(int argc, char **argv)
{
	t_info info;

	(void)argc;
	(void)argv;
	if (argc != 2)
		return(ft_error("Error\nWrong argument count\n"));
	init_file_info(&info);
	if(file_parsing(&info, argv[1]) == -1)
		return (1);
	// initialize_map(&info);
	initialize_mlx(&info);
	mlx_hook(info.win.mlx_win, 17, 0L, quit_program, &info);
	mlx_loop(info.mlx);
}
