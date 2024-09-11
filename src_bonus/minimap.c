/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:19:59 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/09/11 19:32:51 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void my_mlx_pixel_put2(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
    {
        dst = img->addr + (y * img->s_line + x * (img->bt / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_rect(t_data *data, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put2(data->minimap->img, x + i, y + j, color);
			j++;
		}
		i++;
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
	data->minimap->offset_x = WIN_WIDTH - MINIMAP_SIZE - OFFSET_X;
	data->minimap->offset_y = OFFSET_Y;
	data->minimap->img = malloc(sizeof(t_img));
	data->minimap->img->p_img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->minimap->img->p_img)
	{
		printf("Erreur lors de la création de l'image de la minimap\n");
		return;
	}
	data->minimap->img->addr = mlx_get_data_addr(data->minimap->img->p_img, \
		&data->minimap->img->bt, &data->minimap->img->s_line, &data->minimap->img->endian);
}

void	draw_minimap_2(t_data *data)
{
	if (data->minimap->y >= 0 && data->minimap->y < \
		data->minimap->map_height && data->minimap->x >= 0 && \
		data->minimap->x < data->minimap->map_width)
	{
		if (data->minimap->map[data->minimap->y][data->minimap->x] == '1')
			draw_rect(data, data->minimap->screen_x, \
				data->minimap->screen_y, 0x000000);
		else
			draw_rect(data, data->minimap->screen_x, \
				data->minimap->screen_y, 0xFFFFFF);
	}
	return ;
}

void	draw_minimap(t_data *data)
{
	data->minimap->start_x = (int)(data->pl->posy - (MINIMAP_SIZE / \
		(2.0 * TILE_SIZE)));
	data->minimap->start_y = (int)(data->pl->posx - (MINIMAP_SIZE / \
		(2.0 * TILE_SIZE)));
	data->minimap->end_x = data->minimap->start_x + MINIMAP_SIZE / TILE_SIZE;
	data->minimap->end_y = data->minimap->start_y + MINIMAP_SIZE / TILE_SIZE;
	data->minimap->y = data->minimap->start_y;
	while (data->minimap->y < data->minimap->end_y)
	{
		data->minimap->x = data->minimap->start_x;
		while (data->minimap->x < data->minimap->end_x)
		{
			data->minimap->screen_x = (data->minimap->x - data->minimap->start_x) \
				* TILE_SIZE;
			data->minimap->screen_y = (data->minimap->y - data->minimap->start_y) \
				* TILE_SIZE;
			draw_minimap_2(data);
			data->minimap->x++;
		}
		data->minimap->y++;
	}
	int player_screen_x = MINIMAP_SIZE / 2 - TILE_SIZE / 2;
	int player_screen_y = MINIMAP_SIZE / 2 - TILE_SIZE / 2;
	draw_rect(data, player_screen_x, player_screen_y, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap->img->p_img, \
		data->minimap->offset_x, data->minimap->offset_y);
}
