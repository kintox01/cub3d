/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:01:22 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/18 12:54:19 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "key.h"

void	key_dir(t_data *data)
{
	if (data->map->map[(int)(data->pl->posx
			- 1.0)][(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx - 1.0 + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy)] = 'T';
	else if (data->map->map[(int)(data->pl->posx
			+ 1.0)][(int)(data->pl->posy)] == 'D')
		data->map->map[(int)(data->pl->posx + 1.0 + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy)] = 'T';
	else if (data->map->map[(int)(data->pl->posx)][(int)(data->pl->posy
			+ 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy + 1.0)] = 'T';
	else if (data->map->map[(int)(data->pl->posx)][(int)(data->pl->posy
			- 1.0)] == 'D')
		data->map->map[(int)(data->pl->posx + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy - 1.0)] = 'T';
}

void	key_dir2(t_data *data)
{
	if (data->map->map[(int)(data->pl->posx
			- 1.0)][(int)(data->pl->posy)] == 'T')
		data->map->map[(int)(data->pl->posx - 1.0 + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy)] = 'D';
	else if (data->map->map[(int)(data->pl->posx
			+ 1.0)][(int)(data->pl->posy)] == 'T')
		data->map->map[(int)(data->pl->posx + 1.0 + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy)] = 'D';
	else if (data->map->map[(int)(data->pl->posx)][(int)(data->pl->posy
			+ 1.0)] == 'T')
		data->map->map[(int)(data->pl->posx + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy + 1.0)] = 'D';
	else if (data->map->map[(int)(data->pl->posx)][(int)(data->pl->posy
			- 1.0)] == 'T')
		data->map->map[(int)(data->pl->posx + data->pl->dirx
				* data->pl->dey)][(int)(data->pl->posy - 1.0)] = 'D';
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
	if (key == ENTER)
		key_dir(data);
	if (key == LETTER_KEY_ACTION)
		key_dir2(data);
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
