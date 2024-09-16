/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:14:26 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 14:45:35 by hulefevr         ###   ########.fr       */
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
	{
        mlx_destroy_image(data->mlx, data->minimap->img->p_img);
	}
	if (data->anim)
	{
		pthread_mutex_destroy(&data->anim->lock);
		data->anim->status = 0;
		pthread_join(data->anim->thread, NULL);
		printf("Thread %ld freed\n", data->anim->thread);
	}
	free(data->minimap->map);
	free(data->minimap->img);
	free(data->minimap);
}

void	free_my_data(t_data *data)
{
	int i;
	
	i = -1;
	while (++i < 5)
	{
		printf("Weapon %p freed\n", data->weapon[i]->p_img);
		if (data->weapon[i]->p_img)
			mlx_destroy_image(data->mlx, data->weapon[i]->p_img);
		if (data->weapon[i])
			free(data->weapon[i]);
	}
	free(data->weapon);
	free_minimap(data);
	if (data->p_img)
		mlx_destroy_image(data->mlx, data->p_img);
	if (data->hud)
		mlx_destroy_image(data->mlx, data->hud);
	if (data->img_bg)
		mlx_destroy_image(data->mlx, data->img_bg);
	printf("Hud %p freed\n", data->hud);
	if (data->anim)
		free(data->anim);
	
	return ;
	
}

void	free_init_data(t_data *data)
{
	int	i;

	i = 0;
	free(data->pl);
	free(data->dda);
	free(data->t);
	free(data->sp->buffer);
	free(data->sp);
	if (data->img[0])
		free(data->img[0]);
	while (++i < 6)
	{
		if (data->img[i] != NULL && data->img[i]->p_img != NULL)
		{
			mlx_destroy_image(data->mlx, data->img[i]->p_img);
			data->img[i]->p_img = NULL;
		}
		printf("Texture %i %p freed\n", i, data->img[i]->p_img);
		if (data->img[i])
			free(data->img[i]);
	}
	mlx_destroy_window(data->mlx, data->mlx_win);
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
