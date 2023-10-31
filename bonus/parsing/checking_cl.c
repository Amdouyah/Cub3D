/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_cl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:12:10 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/31 20:33:22 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3dbonus.h"

int	fill_color(t_info *glo)
{
	filling(glo->map.flor);
	filling(glo->map.ciling);
	glo->flor_table = ft_split(glo->map.flor, ' ');
	glo->cling_table = ft_split(glo->map.ciling, ' ');
	if (ft_strlen(glo->cling_table[0]) != 1
		|| ft_strlen(glo->flor_table[0]) != 1
		|| ft_strncmp(glo->cling_table[0], "C", ft_strlen(glo->cling_table[0]))
		|| ft_strncmp(glo->flor_table[0], "F", ft_strlen(glo->flor_table[0])))
		return (1);
	if (table_counter(glo->flor_table) != 4
		|| table_counter(glo->cling_table) != 4)
		return (1);
	glo->flor.red = ft_atoi(glo->flor_table[1]);
	glo->flor.green = ft_atoi(glo->flor_table[2]);
	glo->flor.blue = ft_atoi(glo->flor_table[3]);
	glo->cling.red = ft_atoi(glo->cling_table[1]);
	glo->cling.green = ft_atoi(glo->cling_table[2]);
	glo->cling.blue = ft_atoi(glo->cling_table[3]);
	if (checking_inter(glo->flor) || checking_inter(glo->cling))
		return (1);
	free_cl_tab(glo);
	return (0);
}

int	counting_cama(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (0);
	return (1);
}

void	checking_colors(t_info *glo)
{
	if (counting_cama(glo->map.ciling)
		|| counting_cama(glo->map.flor) || fill_color(glo))
	{
		error("map error\n");

		free_tx_tab(glo);
		free_table(glo->file);
		exit(1);
	}
	is_map_valid(glo);
}
