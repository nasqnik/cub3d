/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saherrer <saherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:33:18 by saherrer          #+#    #+#             */
/*   Updated: 2025/05/22 22:25:39 by saherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	quit_program(t_info *info)
{
	ft_free_file("Thanks for playing!\n", info);
	if (info->mlx != NULL)
	{
		if (info->mlx_win != NULL)
		{
			mlx_destroy_window(info->mlx, info->mlx_win);
			if (info->_img != NULL)
				mlx_destroy_image(info->mlx, info->_img);
		}
		free(info->mlx);
		destroy_textures(info);
	}
	exit(0);
}

int	quit_program_message(char *message, t_info *info)
{
	ft_free_file(message, info);
	if (info->mlx != NULL)
	{
		if (info->mlx_win != NULL)
		{
			mlx_destroy_window(info->mlx, info->mlx_win);
			if (info->_img != NULL)
				mlx_destroy_image(info->mlx, info->_img);
		}
		free(info->mlx);
		destroy_textures(info);
	}
	exit(0);
}

double	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
