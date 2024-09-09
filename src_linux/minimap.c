/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:19:59 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/09/09 17:13:20 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_dat_map2(t_data *data, int i, int j)
{
	int k;
	int l;

	if (data->minimap->map[data->minimap->map_y][data->minimap->map_x] == '1')
	{
		data->minimap->mini_x = j * MAP_SCALE;
		data->minimap->mini_y = i * MAP_SCALE;
		k = 0;
		while (k < MAP_SCALE)
		{
			l = 0;
			while (l < MAP_SCALE)
			{
				draw_pixel_img(data->minimap->mini_x + k, \
					data->minimap->mini_y + l, 0x000000, MINIMAP_SIZE, \
						data->minimap->img_data);
				l++;
			}
			k++;
		}
	}
}

void	draw_dat_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->minimap->visible_tiles_y)
	{
		j = 0;
		while (j < data->minimap->visible_tiles_x)
		{
			data->minimap->map_x = (int)(data->minimap->offset_x + j);
			data->minimap->map_y = (int)(data->minimap->offset_y + i);
			draw_dat_map2(data, i, j);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	data->minimap->offset_x = data->pl->plx / MAP_SCALE - \
		data->minimap->visible_tiles_x / 2.0;
	data->minimap->offset_y = data->pl->ply / MAP_SCALE - \
		data->minimap->visible_tiles_y / 2.0;
	if (data->minimap->offset_x < 0)
		data->minimap->offset_x = 0;
	if (data->minimap->offset_y < 0)
		data->minimap->offset_y = 0;
	if (data->minimap->offset_x + data->minimap->visible_tiles_x > \
		data->minimap->map_width)
		data->minimap->offset_x = data->minimap->map_width - \
			data->minimap->visible_tiles_x;
	if (data->minimap->offset_y + data->minimap->visible_tiles_y > \
		data->minimap->map_height)
		data->minimap->offset_y = data->minimap->map_height - \
			data->minimap->visible_tiles_y;
	data->minimap->img_data = mlx_get_data_addr(data->minimap->img, &data->minimap->bpp, \
		&data->minimap->size_line, &data->minimap->endian);
	draw_dat_map(data);
	display_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->img,
		WIN_WIDTH - MINIMAP_SIZE - 10, 10);
}

void    display_player(t_data *data)
{
	int player_x = MINIMAP_SIZE / 2;
	int player_y = MINIMAP_SIZE / 2;

	int k = -3;
	while (k <= 3)
	{
		int l = -3;
		while (l <= 3)
		{
			draw_pixel_img(player_x + k, player_y + l, 0xFF0000, MINIMAP_SIZE,
				data->minimap->img_data);
			l++;
		}
		k++;
	}
}