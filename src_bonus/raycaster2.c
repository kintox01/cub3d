/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguerin <dguerin@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:14:59 by dguerin           #+#    #+#             */
/*   Updated: 2024/09/25 16:58:27 by dguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_dda(t_data *ptr)
{
	ptr->dda->cam_x = 2 * (double)ptr->dda->screenx / (double)WIN_WIDTH - 1;
	ptr->dda->raydir_x = ptr->pl->dirx + ptr->pl->plx * ptr->dda->cam_x;
	ptr->dda->raydir_y = ptr->pl->diry + ptr->pl->ply * ptr->dda->cam_x;
	ptr->dda->map_x = (int)ptr->pl->posx ;
	ptr->dda->map_y = (int)ptr->pl->posy;
	ptr->dda->deltadist_x = fabs(1 / ptr->dda->raydir_x);
	ptr->dda->deltadist_y = fabs(1 / ptr->dda->raydir_y);
	check_side(ptr);
	check_dist(ptr);
}

void	raycaster(t_data *data)
{
	data->dda->screenx = 0;
	while (data->dda->screenx < WIN_WIDTH)
	{
		calc_dda(data);
		run_draw(data);
		data->dda->screenx++;
	}
}
