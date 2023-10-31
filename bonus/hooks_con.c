/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_con.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:07:11 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/31 17:07:30 by bgannoun         ###   ########.fr       */
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

void	ft_mouse(t_cub *cb)
{
	mlx_get_mouse_pos(cb->mlx, &cb->x_mouse_tmp, &cb->y_mouse_tmp);
	if (cb->x_mouse_tmp > cb->x_mouse && cb->x_mouse_tmp > 0
		&& cb->x_mouse_tmp < WIDTH && cb->y_mouse_tmp > 0
		&& cb->y_mouse_tmp < HEIGHT)
		cb->view_p += 0.05;
	else if (cb->x_mouse_tmp < cb->x_mouse && cb->x_mouse_tmp > 0
		&& cb->x_mouse_tmp < WIDTH && cb->y_mouse_tmp > 0
		&& cb->y_mouse_tmp < HEIGHT)
		cb->view_p -= 0.05;
}
