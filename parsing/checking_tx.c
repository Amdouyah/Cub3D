/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_tx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:10:19 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 20:24:28 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_path_valid(t_info *glo)
{
	if (open(glo->no_path, O_RDONLY) == -1 || open(glo->so_path, O_RDONLY) == -1
		|| open(glo->we_path, O_RDONLY) == -1
		|| open(glo->ea_path, O_RDONLY) == -1)
	{
		exit(1);
	}
}

void	checking_paths(t_info *glo, int count_tx, int count_cl)
{
	if (count_tx != 4 || count_cl != 2 || ft_strlen(glo->no[0]) != 2
		|| ft_strlen(glo->so[0]) != 2 || ft_strlen(glo->we[0]) != 2
		|| ft_strlen(glo->ea[0]) != 2 || table_counter(glo->no) != 2
		|| table_counter(glo->so) != 2 || table_counter(glo->we) != 2
		|| table_counter(glo->ea) != 2)
	{
		error("map error\n");
		exit(1);
	}
	glo->no_path = glo->no[1];
	glo->so_path = glo->so[1];
	glo->we_path = glo->we[1];
	glo->ea_path = glo->ea[1];
	is_path_valid(glo);
}
