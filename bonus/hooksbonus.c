/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooksbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:04:35 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/31 17:07:33 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	ft_hook_con(t_cub *cb)
{
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

void	ft_hook(void *p)
{
	t_cub	*cb;

	cb = p;
	cb->xtmp = cb->x_p;
	cb->ytmp = cb->y_p;
	cb->x_mouse_tmp = cb->x_mouse;
	cb->y_mouse_tmp = cb->y_mouse;
	ft_mouse(cb);
	ft_hook_con(cb);
}
