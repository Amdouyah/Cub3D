/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:04:35 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 08:51:04 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	ft_hook(void *p)
{
	t_cub	*cb;

	cb = p;
	cb->xtmp = cb->x_p;
	cb->ytmp = cb->y_p;
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
		minimap(cb);
	}
}
