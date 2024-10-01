/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguerin <dguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:23:10 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/10/01 15:28:21 by dguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*load_image(t_data *data, char *path)
{
	int		i;
	int		j;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, path, &i, &j);
	if (!img)
	{
		printf("Failed to load image: %s\n", path);
		exit(1);
	}
	return (img);
}

void	draw_menu(t_data *data)
{
	data->img_bg = load_image(data, "./res/menu/but.xpm");
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_bg, 0, 0);
}
