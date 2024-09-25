/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguerin <dguerin@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:01:26 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/24 21:17:20 by dguerin          ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
		data->weapon[data->anim->i]->p_img, 323, 498);
	pthread_mutex_unlock(&data->anim->lock);
	draw_minimap(data);
	mlx_do_sync(data->mlx);
	return (0);
}

void	cub(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
    mlx_string_put(data->mlx, data->mlx_win, WIN_WIDTH / 2 - 50, WIN_HEIGHT / 2, \
		0xFFFFFF, "Le jeu est en cours...");
	pthread_mutex_init(&data->anim->lock, NULL);
	pthread_create(&data->anim->thread, NULL, display_hud, data);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_exit, data);
	mlx_hook(data->mlx_win, 17, 0, free_exit, data);
	mlx_loop_hook(data->mlx, launch_game, data);
	mlx_loop(data->mlx);
	pthread_join(data->anim->thread, NULL);
	pthread_mutex_destroy(&data->anim->lock);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		if (x >= 350 && x <= 550 && y >= 375 && y <= 415)
		{
			data->menu_active = 0;
			data->game_started = 1;
			mlx_mouse_hide(data->mlx, data->mlx_win);
			mlx_mouse_move(data->mlx, data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
			cub(data);
		}
		if (x >= 200 && x <= 250 && y >= 450 && y <= 490)
			system("vlc ./res/prout.mp3 &");
		if (x >= 620 && x <= 665 && y >= 450 && y <= 490)
			system("vlc ./res/pete.mp3 &");
	}
	return (0);
}

int	free_exit_menu(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);
	exit(0);
	return (0);
}

int	key_handler_menu(int key, t_data *data)
{
	if (key == KEY_ESC)
		free_exit_menu(data);
	if (data->menu_active == 1 && key == ENTER)
	{
		data->menu_active = 0;
		data->game_started = 1;
		mlx_mouse_hide(data->mlx, data->mlx_win);
		mlx_mouse_move(data->mlx, data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		cub(data);
	}
	return (0);
}	

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	map;

	if (ac != 2)
		return (write_error("Need exactly one parameter (./cub3D <map>.cub)"));
	data = malloc(sizeof(t_data));
	if (!data)
		exit (write_error("Error\nMalloc failed\n"));
	data->mlx = mlx_init();
	if (init_data(data))
		return (1);
	map_init(&map, data);
	if (parsing(data, &map, av))
		free_exit(data);
	mlx_mouse_move(data->mlx, data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	data->n_sprites = ft_lstsize(data->map->item);
	set_spawn(data);
	set_plane(data, data->map->dirspawn);
	data->menu_active = 1;
	data->game_started = 0;
	draw_menu(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_handler_menu, data);
	mlx_hook(data->mlx_win, 17, 0, free_exit_menu, data);
	mlx_mouse_hook(data->mlx_win, mouse_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
