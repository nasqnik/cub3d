/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:25:54 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/24 22:17:02 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		i++;
	}
}

void	destroy_textures(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (info->textures[i].tex != NULL)
			mlx_destroy_image(info->mlx, info->textures[i].tex);
		i++;
	}
}

void	load_textures(t_info *info)
{
	int		i;
	int		bpp;
	int		size;
	int		endian;
	char	*paths[4];

	paths[0] = info->no_path;
	paths[1] = info->so_path;
	paths[2] = info->ea_path;
	paths[3] = info->we_path;
	i = 0;
	while (i < 4)
	{
		info->textures[i].tex = mlx_xpm_file_to_image(info->mlx, paths[i],
				&info->textures[i].img_width, &info->textures[i].img_height);
		if (!info->textures[i].tex)
			quit_program_message("Error: texture file is invalid\n", info);
		info->textures[i].data = (int *)mlx_get_data_addr(
				info->textures[i].tex, &bpp, &size, &endian);
		if (!info->textures[i].data)
			quit_program_message("Error: texture data is invalid\n", info);
		i++;
	}
}
