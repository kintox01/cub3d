/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguerin <dguerin@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:01:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/25 17:16:17 by dguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "key.h"

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

void	key_dir(t_data *data)
{
	if (data->map->map[(int)(data->pl->posx - 1.0)] \
			[(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx - 1.0 + data->pl->dirx \
			* data->pl->dey)][(int)(data->pl->posy)] = '0';
	else if (data->map->map[(int)(data->pl->posx + 1.0)] \
			[(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx + 1.0 + data->pl->dirx \
			* data->pl->dey)][(int)(data->pl->posy)] = '0';
	else if (data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy + 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx \
				* data->pl->dey)][(int)(data->pl->posy + 1.0)] = '0';
	else if (data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy - 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx * \
				data->pl->dey)][(int)(data->pl->posy - 1.0)] = '0';
}

void	spawn_changer(int key, t_data *data)
{
	if (key == KEY_UP)
	{
		data->map->spawn = data->map->spawn->next;
		set_spawn(data);
		set_plane(data, data->map->dirspawn);
	}
	if (key == KEY_DOWN)
	{
		data->map->spawn = data->map->spawn->prev;
		set_spawn(data);
		set_plane(data, data->map->dirspawn);
	}
}

int	key_handler(int key, t_data *data)
{
	if (key == KEY_ESC)
		free_exit(data);
	if (key == 14)
		key_dir(data);
	if (key == KEY_W)
		data->pl->dey = 0.07;
	if (key == KEY_S)
		data->pl->dey = -0.07;
	if (key == KEY_D)
		data->pl->dex = 0.07;
	if (key == KEY_A)
		data->pl->dex = -0.07;
	if (key == KEY_LEFT)
		data->pl->rot = 0.07;
	if (key == KEY_RIGHT)
		data->pl->rot = -0.07;
	spawn_changer(key, data);
	return (0);
}
