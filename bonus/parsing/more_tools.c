/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:02:38 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/21 14:54:20 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	table_counter(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return (0);
	while (table[i])
		i++;
	return (i);
}

int	checking_inter(t_colors color)
{
	if (color.red < 0 || color.red > 255)
		return (1);
	if (color.green < 0 || color.green > 255)
		return (1);
	if (color.blue < 0 || color.blue > 255)
		return (1);
	return (0);
}

int	is_found(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	filling(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_found(",\t", str[i]))
			str[i] = ' ';
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
