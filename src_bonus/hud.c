/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:43:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/06 13:54:01 by hulefevr         ###   ########.fr       */
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
	data->weapon = malloc(sizeof(t_weapon *) * 5);
	if (!data->weapon)
		free_exit(data);
	while (++i < 5)
	{
		data->weapon[i] = malloc(sizeof(t_weapon));
		if (!data->weapon[i])
			free_exit(data);
	}
	init_weapon(data, WEAPON0, 0);
	init_weapon(data, WEAPON1, 1);
	init_weapon(data, WEAPON2, 2);
	init_weapon(data, WEAPON3, 3);
	init_weapon(data, WEAPON4, 4);
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

void	display_hud(t_data *data, int flag)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon[flag]->p_img, 0, 0);
	return ;
}
