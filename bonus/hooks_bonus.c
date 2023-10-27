/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:23:54 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/27 12:43:12 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	ft_up(t_cub *cb)
{
	cb->xtmp += cos(cb->view_p) * SPEED;
	cb->ytmp += sin(cb->view_p) * SPEED;
}

void	ft_left(t_cub *cb)
{
	cb->xtmp -= cos(cb->view_p + rad(90)) * SPEED;
	cb->ytmp -= sin(cb->view_p + rad(90)) * SPEED;
}
void	ft_down(t_cub *cb)
{
	cb->xtmp -= cos(cb->view_p) * SPEED;
	cb->ytmp -= sin(cb->view_p) * SPEED;
}

void	ft_right(t_cub *cb)
{
	cb->xtmp += cos(cb->view_p + rad(90)) * SPEED;
	cb->ytmp += sin(cb->view_p + rad(90)) * SPEED;
}
void	ft_mv_left(t_cub *cb)
{
	cb->view_p -= 0.05;
	if (cb->view_p >= 0)
		cb->view_p -= 2*M_PI;
	else if (cb->view_p < 2*M_PI)
		cb->view_p += 2*M_PI;
}

void	ft_mv_right(t_cub *cb)
{
	cb->view_p += 0.05;
	if (cb->view_p >= 0)
		cb->view_p -= 2 * M_PI;
	else if (cb->view_p < 2 * M_PI)
		cb->view_p += 2 * M_PI;
}
int	wall_check(t_cub *cb)
{
	if ((cb->map[(int)(cb->y_p) / TILE_SIZE][(int)cb->xtmp / TILE_SIZE] != '1'
		&& cb->map[(int)(cb->ytmp)/TILE_SIZE][(int)cb->x_p/TILE_SIZE] != '1'
		&& cb->map[(int)cb->ytmp/TILE_SIZE][(int)(cb->xtmp) / TILE_SIZE] != '1'))
		return (1);
	return (0);
}
