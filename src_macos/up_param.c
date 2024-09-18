
#include "../inc/cub3d.h"

void	update_param(t_data *data, double rot)
{
	double	olddirx;
	double	oldplanex;

	olddirx = data->pl->dirx;
	data->pl->totalrots += rot;
	data->pl->dirx = data->pl->dirx * cos(rot) - data->pl->diry * sin(rot);
	data->pl->diry = olddirx * sin(rot) + data->pl->diry * cos(rot);
	oldplanex = data->pl->plx;
	data->pl->plx = data->pl->plx * cos(rot) - data->pl->ply * sin(rot);
	data->pl->ply = oldplanex * sin(rot) + data->pl->ply * cos(rot);
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx + \
			data->pl->dirx * data->pl->dey)][(int)(data->pl->posy)]))
		data->pl->posx += data->pl->dirx * data->pl->dey;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx)] \
			[(int)(data->pl->posy + data->pl->diry * data->pl->dey)]))
		data->pl->posy += data->pl->diry * data->pl->dey;
	if (!ft_strchr("1D", data->map->map[(int)(data->pl->posx + \
			data->pl->plx * data->pl->dex)][(int)data->pl->posy]))
		data->pl->posx += data->pl->plx * data->pl->dex;
	if (!ft_strchr("1D", data->map->map[(int)data->pl->posx] \
			[(int)(data->pl->posy + data->pl->ply * data->pl->dex)]))
		data->pl->posy += data->pl->ply * data->pl->dex;
}
