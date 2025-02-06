/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:14:26 by hulefevr          #+#    #+#             */
/*   Updated: 2025/02/06 15:27:35 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_dat_img(t_data *data)
{
	int	i;

	i = 0;
	while (++i < 6)
	{
		if (data->img[i] != NULL && data->img[i]->p_img != NULL)
		{
			mlx_destroy_image(data->mlx, data->img[i]->p_img);
			data->img[i]->p_img = NULL;
		}
		if (data->img[i])
			free(data->img[i]);
	}
}

void	free_init_data(t_data *data)
{
	free(data->pl);
	free(data->dda);
	free(data->t);
	free(data->sp->buffer);
	free(data->sp);
	if (data->img[0])
		free(data->img[0]);
	free_dat_img(data);
	if (data->p_img)
		mlx_destroy_image(data->mlx, data->p_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->img);
	free(data->mlx);
	free(data);
	return ;
}

int	free_exit(t_data *data)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	tmp = data->map->item;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp->content);
		tmp = tmp->next;
		free(tmp2);
	}
	i = -1;
	if (data->map && data->map->map)
		while (data->map->map[++i])
			free(data->map->map[i]);
	free(data->map->map);
	dlst_free(&data->map->spawn);
	free_init_data(data);
	exit(0);
}
