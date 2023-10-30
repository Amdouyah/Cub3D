/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:18:54 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 16:42:26 by amdouyah         ###   ########.fr       */
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
	if ((cb->map[(int)(cb->y_p) / TILE_SIZE][(int)cb->xtmp / TILE_SIZE] != '1'
			&& cb->map[(int)(cb->ytmp) / TILE_SIZE][(int)cb->x_p
			/ TILE_SIZE] != '1' && cb->map[(int)cb->ytmp
			/ TILE_SIZE][(int)(cb->xtmp) / TILE_SIZE] != '1'))
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
