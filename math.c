/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:23:47 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/27 16:43:18 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rad(float degree)
{
	return (degree * M_PI / 180);
}

int ft_abs(int n)
{ 
	if (n < 0)
		return (n * (-1));
	return (n);
}

float	normlizeAngle(float angle)
{
	if (angle < 0)
        angle += (2 * M_PI);
    else
        angle = remainder(angle, 2 * M_PI);
    return (angle);
}

void	dda(int xi, int yi, int xf, int yf, t_cub *map)
{
	int		dy;
	int		dx;
	float	yinc;
	float	xinc;
	int		steps;
	float	x;
	float	y;

	dy = yf - yi;
	dx = xf - xi;
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else 
		steps = ft_abs(dy);
	yinc = dy / (float)steps; //point to point in x
	xinc = dx / (float)steps;
	x = xi;
	y = yi;
	while (steps)
	{
		mlx_put_pixel(map->img, x, y, r_g_b(255,255,255,255));
		x += xinc;
		y += yinc;
		steps--;
	}
}

