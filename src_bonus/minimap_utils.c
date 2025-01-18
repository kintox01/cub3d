/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:45:37 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/18 12:45:44 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put2(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
	{
		dst = img->addr + (y * img->s_line + x * (img->bt / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rect(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

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
