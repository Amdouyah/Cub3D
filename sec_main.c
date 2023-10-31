/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:53:34 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/31 18:24:44 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sec_minimap(t_cub *cb)
{
	int		i;
	float	inc;

	i = 0;
	inc = rad(FOV) / WIDTH;
	cb->rayangle = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		castray(cb, i);
		cb->rayangle += inc;
		i++;
	}
}

void	minimap(t_cub *cb)
{
	int		i;
	int		j;

	ft_ceil(cb);
	ft_floor(cb);
	i = -1;
	while (cb->map[++i])
	{
		j = -1;
		while (cb->map[i][++j])
		{
			if (cb->map[i][j] == 'N' || cb->map[i][j] == 'S'
				|| cb->map[i][j] == 'W' || cb->map[i][j] == 'E')
			{
				if (cb->x_p == -1 && cb->y_p == -1)
				{
					init_view(cb, cb->map[i][j]);
					cb->x_p = j * TILE_SIZE + (TILE_SIZE / 2);
					cb->y_p = i * TILE_SIZE + (TILE_SIZE / 2);
				}
			}
		}
	}
	sec_minimap(cb);
}

void	get_angle_view(t_cub *cb)
{
	cb->rayangle = normlizeangle(cb->rayangle);
	cb->down = 0;
	cb->right = 0;
	cb->up = 0;
	cb->left = 0;
	if (cb->rayangle > 0 && cb->rayangle < M_PI)
		cb->down = 1;
	cb->up = !cb->down;
	cb->right = 0;
	if (cb->rayangle < 0.5 * M_PI || cb->rayangle > 1.5 * M_PI)
		cb->right = 1;
	cb->left = !cb->right;
}
