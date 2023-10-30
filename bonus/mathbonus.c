/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matbonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:23:47 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 16:42:41 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

double	rad(float degree)
{
	return (degree * M_PI / 180);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	return (n);
}

float	normlizeangle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else
		angle = remainder(angle, 2 * M_PI);
	return (angle);
}
