/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:24:37 by dguerin           #+#    #+#             */
/*   Updated: 2025/01/18 12:37:35 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	write_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	write_error0(char *str)
{
	printf("%s", str);
	return (0);
}

int	are_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isspace(str[i++]))
			return (0);
	return (1);
}

int	ft_free(void *a1, void *a2, void *a3, void *a4)
{
	if (a1)
		free(a1);
	if (a2)
		free(a2);
	if (a3)
		free(a3);
	if (a4)
		free(a4);
	return (1);
}

void	ft_tab_len(t_file *file, char **tab)
{
	size_t	i;

	i = file->map_start;
	while (tab[i])
		i++;
	file->tab_len = i - file->map_start;
}
