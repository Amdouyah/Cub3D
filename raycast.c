/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:46:58 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 08:47:35 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_cub *cb, float x, float y)
{
	int	ym;
	int	len_y;
	int	index_x;
	int	index_y;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (1);
	index_x = (int)floor(x / TILE_SIZE);
	index_y = (int)floor(y / TILE_SIZE);
	ym = 0;
	while (cb->map[ym])
		ym++;
	if (index_y >= ym)
		return (1);
	len_y = ft_strlen(cb->map[index_y]);
	if (index_x >= len_y)
		return (1);
	if (cb->map[index_y][index_x] == '1')
		return (1);
	return (0);
}

void	get_horz(t_cub *cb)
{
	float	x_hintercept;
	float	y_hintercept;

	cb->found_horz = 0;
	cb->horzw_x = 0;
	cb->horzw_y = 0;
	y_hintercept = floor(cb->y_p / TILE_SIZE) * TILE_SIZE;
	if (sin(cb->rayangle) > 0)
		y_hintercept += TILE_SIZE;
	x_hintercept = (y_hintercept - cb->y_p) / tan(cb->rayangle);
	if (cos(cb->rayangle) < 0)
		x_hintercept = cb->x_p - fabs(x_hintercept);
	else
		x_hintercept = cb->x_p + fabs(x_hintercept);
	get_hsteps(cb);
	cb->nexthorz_x = x_hintercept;
	cb->nexthorz_y = y_hintercept;
	if (sin(cb->rayangle) < 0)
		cb->nexthorz_y -= 0.001;
	get_horz2(cb);
}

void	get_horz2(t_cub *cb)
{
	float	x_to_check;
	float	y_to_check;

	while (cb->nexthorz_x >= 0 && cb->nexthorz_x <= WIDTH && cb->nexthorz_y >= 0
		&& cb->nexthorz_y <= HEIGHT)
	{
		x_to_check = cb->nexthorz_x;
		y_to_check = 0.0;
		if (cb->up)
			y_to_check = cb->nexthorz_y - 1.0;
		else
			y_to_check = cb->nexthorz_y;
		if (check_wall(cb, x_to_check, y_to_check))
		{
			cb->horzw_x = cb->nexthorz_x;
			cb->horzw_y = cb->nexthorz_y;
			cb->found_horz = 1;
			break ;
		}
		else
		{
			cb->nexthorz_x += cb->x_hstep;
			cb->nexthorz_y += cb->y_hstep;
		}
	}
}

void	get_vert(t_cub *cb)
{
	float	x_vintercept;
	float	y_vintercept;

	cb->vertw_x = 0;
	cb->vertw_y = 0;
	x_vintercept = floor(cb->x_p / TILE_SIZE) * TILE_SIZE;
	if (cos(cb->rayangle) > 0)
		x_vintercept += TILE_SIZE;
	y_vintercept = (x_vintercept - cb->x_p) * tan(cb->rayangle);
	if (sin(cb->rayangle) > 0)
		y_vintercept = cb->y_p + fabs(y_vintercept);
	else
		y_vintercept = cb->y_p - fabs(y_vintercept);
	get_vstep(cb);
	cb->nextvert_x = x_vintercept;
	cb->nextvert_y = y_vintercept;
	cb->found_vert = 0;
	if (cos(cb->rayangle) < 0)
		cb->nextvert_x -= 0.001;
	get_vert2(cb);
}

void	get_vert2(t_cub *cb)
{
	float	xv_tocheck;
	float	yv_tocheck;

	while (cb->nextvert_x >= 0 && cb->nextvert_x <= WIDTH && cb->nextvert_y >= 0
		&& cb->nextvert_y <= HEIGHT)
	{
		xv_tocheck = 0.0;
		if (cb->left)
			xv_tocheck = cb->nextvert_x - 1.0;
		else
			xv_tocheck = cb->nextvert_x;
		yv_tocheck = cb->nextvert_y;
		if (check_wall(cb, xv_tocheck, yv_tocheck))
		{
			cb->vertw_x = cb->nextvert_x;
			cb->vertw_y = cb->nextvert_y;
			cb->found_vert = 1;
			break ;
		}
		else
		{
			cb->nextvert_x += cb->x_vstep;
			cb->nextvert_y += cb->y_vstep;
		}
	}
}
