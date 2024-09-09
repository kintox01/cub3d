/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:19:59 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/09/09 15:38:26 by hugolefevre      ###   ########.fr       */
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
	img_data = mlx_get_data_addr(data->minimap->img, &data->minimap->bpp, &data->minimap->size_line, &data->minimap->endian);
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
}

void	draw_minimap(t_data *data)
{
    int i = 0, j = 0;
    
    int visible_tiles_x = MINIMAP_SIZE / MAP_SCALE;
    int visible_tiles_y = MINIMAP_SIZE / MAP_SCALE;

    double offset_x = data->pl->plx / MAP_SCALE - visible_tiles_x / 2.0;
    double offset_y = data->pl->ply / MAP_SCALE - visible_tiles_y / 2.0;

    if (offset_x < 0)
		offset_x = 0;
    if (offset_y < 0)
		offset_y = 0;
    if (offset_x + visible_tiles_x > data->minimap->map_width)
		offset_x = data->minimap->map_width - visible_tiles_x;
    if (offset_y + visible_tiles_y > data->minimap->map_height)
		offset_y = data->minimap->map_height - visible_tiles_y;

	char *img_data;
	img_data = mlx_get_data_addr(data->minimap->img, &data->minimap->bpp, \
		&data->minimap->size_line, &data->minimap->endian);
	
    i = 0;
    while (i < visible_tiles_y) {
        j = 0;
        while (j < visible_tiles_x)
		{
            int map_x = (int)(offset_x + j);
            int map_y = (int)(offset_y + i);

            if (data->minimap->map[map_y][map_x] == '1')
			{
                int mini_x = j * MAP_SCALE;
                int mini_y = i * MAP_SCALE;

                int k = 0;
                while (k < MAP_SCALE)
				{
                    int l = 0;
                    while (l < MAP_SCALE)
					{
                        draw_pixel_img(mini_x + k, mini_y + l, 0x000000, \
							MINIMAP_SIZE, img_data);
                        l++;
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }

    int player_x = MINIMAP_SIZE / 2;
    int player_y = MINIMAP_SIZE / 2;

    int k = -3;
    while (k <= 3)
	{
        int l = -3;
        while (l <= 3)
		{
            draw_pixel_img(player_x + k, player_y + l, 0xFF0000, MINIMAP_SIZE, img_data);
            l++;
        }
        k++;
    }
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->img, WIN_WIDTH - MINIMAP_SIZE - 10, 10);

}
