
#include "../cub3d.h"

void	initialize_textures(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		info->textures[i].tex = NULL;
		info->textures[i].img_width = IMAGE_WIDTH;
		info->textures[i].img_height = IMAGE_HEIGHT;
        info->textures[i].data = NULL;
	}
}

static int	texture_return(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (info->textures[i].tex == NULL)
			return (1);
		i++;
	}
	return (0);
}

static void	destroy_textures(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (info->textures[i].tex == NULL)
		{
			i++;
			continue ;
		}
		mlx_destroy_image(info->mlx, info->textures[i].tex);
		i++;
	}
}

static void	texture_checker(t_info *info)
{
	if (texture_return(info) == 1)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		destroy_textures(info);
		ft_free_file("image_checker: one of the images is invalid\n", info);
	}
}


void	load_textures(t_info *info)
{
	int		i;
	char	*address;
    int     bpp;
    int     size;
    int     endian;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			address = info->no_path;
		else if (i == 1)
			address = info->so_path;
		else if (i == 2)
			address = info->ea_path;
		else if (i == 3)
			address = info->we_path;
		info->textures[i].tex = mlx_xpm_file_to_image(info->mlx, address,
				&info->textures[i].img_width, &info->textures[i].img_height);
        info->textures[i].data = (int *)mlx_get_data_addr(info->textures[i].tex, &bpp, &size, &endian);
		i++;
	}
	texture_checker(info);
}

