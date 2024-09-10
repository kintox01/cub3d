/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:23:10 by hugolefevre       #+#    #+#             */
/*   Updated: 2024/09/10 15:02:11 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*load_image(t_data *data, char *path)
{
	int	i;
	int	j;
    void *img = mlx_xpm_file_to_image(data->mlx, path, &i, &j);
    if (!img)
	{
        fprintf(stderr, "Failed to load image: %s\n", path);
        exit(1);
    }
    return (img);
}

void draw_menu(t_data *data)
{
	data->img_bg = load_image(data, "./res/menu/but.xpm");
    // data->img_start = load_image(&data, "path/to/start_button.xpm", NULL, NULL);
    // Dessiner l'image de fond du menu
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_bg, 0, 0);

    // Dessiner les boutons
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_start, 100, 200);
}