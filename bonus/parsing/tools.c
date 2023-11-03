/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:01:32 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 22:43:56 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3dbonus.h"

void	free_table(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_tx_tab(t_info *glo)
{
	free_table(glo->no);
	free_table(glo->so);
	free_table(glo->we);
	free_table(glo->ea);
}

void	free_cl_tab(t_info *glo)
{
	free_table(glo->flor_table);
	free_table(glo->cling_table);
}

int	error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	return (1);
}

int	table_count(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (i == 2)
		return (0);
	return (1);
}
