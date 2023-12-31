/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:55:27 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/31 16:51:03 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	draw_sq(mlx_image_t *img, int y, int x, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_S)
	{
		j = -1;
		while (++j < TILE_S)
			mlx_put_pixel(img, j + x, i + y, color);
	}
}

void	drawplayer(t_cub *cb, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			mlx_put_pixel(cb->img, j + y - 2, i + x - 2, r_g_b(255, 205, 75,
					255));
		i++;
	}
}

int	get_position(float ver, float width)
{
	int	pos;

	pos = ((ver / TILE_S) - (int)ver / TILE_S) * width;
	return (pos);
}

void	get_hsteps(t_cub *cb)
{
	cb->y_hstep = TILE_S;
	if (sin(cb->rayangle) < 0)
		cb->y_hstep *= -1;
	cb->x_hstep = TILE_S / tan(cb->rayangle);
	if ((cos(cb->rayangle) < 0 && cb->x_hstep > 0) || (cos(cb->rayangle) > 0
			&& cb->x_hstep < 0))
		cb->x_hstep *= -1;
}

void	get_vstep(t_cub *cb)
{
	cb->x_vstep = TILE_S;
	if (cos(cb->rayangle) < 0)
		cb->x_vstep *= -1;
	cb->y_vstep = TILE_S * tan(cb->rayangle);
	if ((sin(cb->rayangle) > 0 && cb->y_vstep < 0) || (sin(cb->rayangle) < 0
			&& cb->y_vstep > 0))
		cb->y_vstep *= -1;
}
