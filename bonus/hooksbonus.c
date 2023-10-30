/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooksbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:04:35 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 16:42:33 by amdouyah         ###   ########.fr       */
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
		cb->view_p +=  0.05;
	else if (cb->x_mouse_tmp < cb->x_mouse && cb->x_mouse_tmp > 0 
			&& cb->x_mouse_tmp < WIDTH && cb->y_mouse_tmp > 0 
			&& cb->y_mouse_tmp < HEIGHT)
		cb->view_p -=  0.05;
	
}

void	ft_hook(void *p)
{
	t_cub	*cb;

	cb = p;
	cb->xtmp = cb->x_p;
	cb->ytmp = cb->y_p;
	cb->x_mouse_tmp = cb->x_mouse;
	cb->y_mouse_tmp = cb->y_mouse;
	
	ft_mouse(cb);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
		ft_up(cb);
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		ft_left(cb);
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		ft_down(cb);
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		ft_right(cb);
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		ft_mv_left(cb);
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		ft_mv_right(cb);
	if (wall_check(cb))
	{
		cb->x_p = cb->xtmp;
		cb->y_p = cb->ytmp;
		cb->x_mouse = cb->x_mouse_tmp;
		cb->y_mouse = cb->y_mouse_tmp;
		minimap(cb);
	}
}
