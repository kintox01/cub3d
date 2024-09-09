/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:19:59 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/09/09 14:15:59 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_pixel(t_data *data, int x, int y, int color)
{
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
        mlx_pixel_put(data->mlx, data->mlx_win, x, y, color);
}

void	clear_screen(t_data *data) {
    int x;
	int y;

	y = 0;
    while (y < WIN_HEIGHT)
	{
		x = 0;
        while (x < WIN_WIDTH)
		{
            draw_pixel(data, x, y, 0x000000);
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
}

void	draw_minimap(t_data *data)
{
    int i = 0, j = 0;
    
    int visible_tiles_x = MINIMAP_SIZE / MAP_SCALE;
    int visible_tiles_y = MINIMAP_SIZE / MAP_SCALE;

    double offset_x = data->pl->dex / MAP_SCALE - visible_tiles_x / 2.0;
    double offset_y = data->pl->dey / MAP_SCALE - visible_tiles_y / 2.0;

    if (offset_x < 0)
		offset_x = 0;
    if (offset_y < 0)
		offset_y = 0;
    if (offset_x + visible_tiles_x > data->minimap->map_width)
		offset_x = data->minimap->map_width - visible_tiles_x;
    if (offset_y + visible_tiles_y > data->minimap->map_height)
		offset_y = data->minimap->map_height - visible_tiles_y;
    i = 0;
    while (i < visible_tiles_y) {
        j = 0;
        while (j < visible_tiles_x)
		{
            int map_x = (int)(offset_x + j);
            int map_y = (int)(offset_y + i);

            if (data->minimap->map[map_y][map_x] == '1')
			{
                int mini_x = j * MAP_SCALE + (WIN_WIDTH - MINIMAP_SIZE - 10);
                int mini_y = i * MAP_SCALE + 10;

                int k = 0;
                while (k < MAP_SCALE)
				{
                    int l = 0;
                    while (l < MAP_SCALE)
					{
                        draw_pixel(data, mini_x + k, mini_y + l, 0xFFFFFF); // Blanc pour les murs
                        l++;
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }

    int player_x = WIN_WIDTH - MINIMAP_SIZE / 2 - 10;
    int player_y = 10 + MINIMAP_SIZE / 2;

    int k = -3;
    while (k <= 3)
	{
        int l = -3;
        while (l <= 3)
		{
            draw_pixel(data, player_x + k, player_y + l, 0xFF0000); // Rouge pour le joueur
            l++;
        }
        k++;
    }
}
