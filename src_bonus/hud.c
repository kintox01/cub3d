/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:43:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 12:48:41 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_weapon(t_data *data, char *path, int flag)
{
	int		width;
	int		height;
	void	*weapon_ptr;

	weapon_ptr = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	data->weapon[flag]->p_img = weapon_ptr;
	data->weapon[flag]->width = width;
	data->weapon[flag]->height = height;
	return ;
}

void	create_weapon(t_data *data)
{
	int	i;

	i = -1;
	data->anim = malloc(sizeof(t_animation));
	data->weapon = malloc(sizeof(t_weapon *) * 5);
	if (!data->weapon)
		free_exit(data);
	while (++i < 5)
	{
		data->weapon[i] = malloc(sizeof(t_weapon));
		if (!data->weapon[i])
			free_exit(data);
	}
	data->anim->i = 0;
	init_weapon(data, WEAPON0, 0);
	init_weapon(data, WEAPON1, 1);
	init_weapon(data, WEAPON2, 2);
	init_weapon(data, WEAPON3, 3);
	init_weapon(data, WEAPON4, 4);
	data->anim->status = 1;
	return ;
}

void	init_hud(t_data *data)
{
	int		width;
	int		height;
	void	*hud_ptr;

	hud_ptr = mlx_xpm_file_to_image(data->mlx, HUD, &width, &height);
	data->hud = hud_ptr;
	create_weapon(data);
	return ;
}

void	*display_hud(void *dat)
{
	t_data	*data;

	data = (t_data *)dat;
	(void)dat;
	while (1)
	{
		pthread_mutex_lock(&data->anim->lock);
		data->anim->i = (data->anim->i + 1) % 5;
		pthread_mutex_unlock(&data->anim->lock);
		usleep(170000);
		if (data->anim->status == 0)
		{
			pthread_exit(NULL);
		}
	}
	return (NULL);
}
