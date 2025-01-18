/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:49:56 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/18 12:54:31 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "key.h"

void	map_init(t_map *map, t_data *data)
{
	map->spawn = 0;
	map->item = 0;
	data->t->start = clock();
	data->t->n_frame = 6;
	data->map = map;
	data->t->tmp = 1;
	data->pl->totalrots = 0;
	data->n_taken = 0;
	data->minimap = malloc(sizeof(t_minimap));
}

int	launch_game(t_data *data)
{
	mousing(data);
	update_param(data, data->pl->rot);
	raycaster(data);
	pthread_mutex_lock(&data->anim->lock);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->p_img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->hud, 140, 604);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->weapon[data->anim->i]->p_img, 323, 498);
	pthread_mutex_unlock(&data->anim->lock);
	draw_minimap(data);
	mlx_do_sync(data->mlx);
	return (0);
}

int	key_exit(int key, t_data *data)
{
	if (key == KEY_LEFT)
		data->pl->rot = 0;
	if (key == KEY_RIGHT)
		data->pl->rot = 0;
	if (key == KEY_LEFT)
		data->pl->rot = 0;
	if (key == KEY_RIGHT)
		data->pl->rot = 0;
	if (key == KEY_W)
		data->pl->dey = 0;
	if (key == KEY_S)
		data->pl->dey = 0;
	if (key == KEY_D)
		data->pl->dex = 0;
	if (key == KEY_A)
		data->pl->dex = 0;
	return (0);
}

void	set_dir(t_data *ptr, char flag)
{
	if (flag == 'W')
	{
		ptr->pl->dirx = 1;
		ptr->pl->diry = -1;
	}
	else if (flag == 'E')
	{
		ptr->pl->dirx = 1;
		ptr->pl->diry = 1;
	}
	else if (flag == 'N')
	{
		ptr->pl->diry = 1;
		ptr->pl->dirx = -1;
	}
	else if (flag == 'S')
	{
		ptr->pl->diry = 1;
		ptr->pl->dirx = 1;
	}
}
