/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:14:26 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/11 14:11:10 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"

void free_minimap(t_data *data)
{
    int i = 0;

    while (i < data->minimap->map_height)
    {
        free(data->minimap->map[i]);
        i++;
    }

    if (data->minimap->img->p_img)
        mlx_destroy_image(data->mlx, data->minimap->img->p_img);
	free(data->minimap->img);
}

void	free_my_data(t_data *data)
{
	int i;
	
	i = -1;
	while (++i < 5)
	{
		if (data->weapon[i]->p_img)
			mlx_destroy_image(data->mlx, data->weapon[i]->p_img);
		if (data->weapon[i])
			free(data->weapon[i]);
	}
	free_minimap(data);
	if (data->p_img)
		mlx_destroy_image(data->mlx, data->p_img);
	if (data->hud)
		mlx_destroy_image(data->mlx, data->hud);
	free(data->anim);
	return ;
	
}

void	free_init_data(t_data *data)
{
	int	i;

	i = -1;
	free(data->pl);
	free(data->dda);
	free(data->t);
	free(data->sp->buffer);
	free(data->sp);
	while (++i <= 16)
	{
		// if (data->img[i]->p_img)
		// 	free(data->img[i]->p_img);
		if (data->img[i])
			free(data->img[i]);
	}
	free(data->img);
	free_my_data(data);
	free(data->mlx);
	free(data);
	return ;
}


int	free_exit(t_data *data)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	mlx_destroy_window(data->mlx, data->mlx_win);
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
