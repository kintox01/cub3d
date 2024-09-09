/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:13:01 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/09 17:13:23 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_pixel_img(int x, int y, int color, int img_width, char *data)
{
	int pixel;

	if (x >= 0 && x < img_width && y >= 0)
	{
		pixel = (y * img_width + x) * 4;
		data[pixel] = color;
		data[pixel + 1] = color >> 8;
		data[pixel + 2] = color >> 16;
	}
}


void	clear_minimap(t_data *data) {
	int		x;
	int		y;
	char	*img_data;

	y = 0;
	img_data = mlx_get_data_addr(data->minimap->img, &data->minimap->bpp,
		&data->minimap->size_line, &data->minimap->endian);
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			draw_pixel_img(x, y, 0xFFFFFF, MINIMAP_SIZE, img_data);
			x++;
		}
		y++;
	}
}

void	init_minimap(t_data *data)
{
	int i;

	i = 0;
	while (data->map->map[i])
		i++;
	data->minimap->map_height = i;
	i = 0;
	while (data->map->map[0][i])
		i++;
	data->minimap->map_width = i;
	i = 0;
	data->minimap->map = malloc(sizeof(char *) * (data->minimap->map_height));
	while (data->map->map[i])
	{
		data->minimap->map[i] = ft_strdup(data->map->map[i]);
		i++;
	}
	data->minimap->img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
		data->minimap->visible_tiles_x = MINIMAP_SIZE / MAP_SCALE;
	data->minimap->visible_tiles_y = MINIMAP_SIZE / MAP_SCALE;
	if (data->minimap->visible_tiles_x > data->minimap->map_width)
		data->minimap->visible_tiles_x = data->minimap->map_width;
	if (data->minimap->visible_tiles_y > data->minimap->map_height)
		data->minimap->visible_tiles_y = data->minimap->map_height;
}