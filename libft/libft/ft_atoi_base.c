/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:09:07 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/27 12:22:52 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_is_valid(char c, int base)
{
	char	*base1[17] = "0123456789ABCDEF";
	char	*base2[17] = "0123456789abcdef";

	while (base--)
	{
		if (base[base1] == c || base[base2] == c)
			return (1);
	}
	return (0);
}

int	ft_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
}

int	ft_atoi_base(const char *str, int base)
{
	size_t	i;
	int		j;
	size_t	nombre;

	j = 1;
	i = 0;
	nombre = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (str_is_valid(str[i], base))
	{
		nombre = nombre * base + ft_value(str[i]);
		i++;
	}
	return (nombre * j);
}
