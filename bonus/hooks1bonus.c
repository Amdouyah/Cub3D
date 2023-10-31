/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:18:54 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/31 16:48:19 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	ft_mv_left(t_cub *cb)
{
	cb->view_p -= 0.03;
	if (cb->view_p >= 0)
		cb->view_p -= 2 * M_PI;
	else if (cb->view_p < 2 * M_PI)
		cb->view_p += 2 * M_PI;
}

void	ft_mv_right(t_cub *cb)
{
	cb->view_p += 0.03;
	if (cb->view_p >= 0)
		cb->view_p -= 2 * M_PI;
	else if (cb->view_p < 2 * M_PI)
		cb->view_p += 2 * M_PI;
}

int	wall_check(t_cub *cb)
{
	if ((cb->map[(int)(cb->y_p) / TILE_S][(int)cb->xtmp / TILE_S] != '1'
			&& cb->map[(int)(cb->ytmp) / TILE_S][(int)cb->x_p
			/ TILE_S] != '1' && cb->map[(int)cb->ytmp
			/ TILE_S][(int)(cb->xtmp) / TILE_S] != '1'))
		return (1);
	return (0);
}

void	init_view(t_cub *cb, char c)
{
	if (c == 'N')
		cb->view_p = 3 * M_PI / 2;
	else if (c == 'W')
		cb->view_p = M_PI;
	else if (c == 'E')
		cb->view_p = 0;
	else if (c == 'S')
		cb->view_p = M_PI / 2;
}
