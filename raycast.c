/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:46:58 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 08:14:29 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(t_cub *cb ,float x, float y)
{
	int	ym;
	int	len_y;
	int	index_x;
	int	index_y;
  // Check if the x and y coordinates are within the bounds of the map.
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
	float	x_Hintercept;
	float	y_Hintercept;
	
	cb->found_horz = 0;
	cb->horzW_x = 0;
	cb->horzW_y = 0;
	y_Hintercept = floor(cb->y_p / TILE_SIZE) * TILE_SIZE; 
	if (sin(cb->rayAngle) > 0)
		y_Hintercept += TILE_SIZE;
	x_Hintercept = (y_Hintercept - cb->y_p) / tan(cb->rayAngle);
	if (cos(cb->rayAngle) < 0)
		x_Hintercept = cb->x_p - fabs(x_Hintercept);
	else
		x_Hintercept = cb->x_p + fabs(x_Hintercept);
	get_hsteps(cb);
	cb->nextHorz_x = x_Hintercept;
	cb->nextHorz_y = y_Hintercept;
	if (sin(cb->rayAngle) < 0)
		cb->nextHorz_y -= 0.001;
	get_horz2(cb);
}

void	get_horz2(t_cub *cb)
{
	float	xTocheck;
	float	yTocheck;
	
	while (cb->nextHorz_x >= 0 && cb->nextHorz_x <= WIDTH && cb->nextHorz_y >= 0 && cb->nextHorz_y <= HEIGHT)
	{
		xTocheck = cb->nextHorz_x;
		yTocheck = 0.0;
		if (cb->up)
    		yTocheck = cb->nextHorz_y - 1.0;
		else
   			 yTocheck = cb->nextHorz_y;
		if (check_wall(cb , xTocheck, yTocheck))
		{
			cb->horzW_x = cb->nextHorz_x;
			cb->horzW_y = cb->nextHorz_y;
			cb->found_horz = 1;
			break ;
		}
		else
		{
			cb->nextHorz_x += cb->x_hstep;
			cb->nextHorz_y += cb->y_hstep;
		}
	}
}


void	get_vert(t_cub *cb)
{
	float	x_Vintercept; 
	float	y_Vintercept;

	cb->VertW_x = 0;
	cb->VertW_y = 0;
	x_Vintercept = floor(cb->x_p / TILE_SIZE) * TILE_SIZE; 
	if (cos(cb->rayAngle) > 0)
		x_Vintercept += TILE_SIZE;
	y_Vintercept = (x_Vintercept - cb->x_p) * tan(cb->rayAngle);
	
	if(sin(cb->rayAngle) > 0)
		y_Vintercept = cb->y_p + fabs(y_Vintercept);
	else
		y_Vintercept = cb->y_p - fabs(y_Vintercept);
	get_vstep(cb);
	cb->nextVert_x = x_Vintercept;
	cb->nextVert_y = y_Vintercept;
	cb->found_vert = 0;
	if (cos(cb->rayAngle) < 0)
		cb->nextVert_x -= 0.001;
	get_vert2(cb);
}

void	get_vert2(t_cub *cb)
{
	while (cb->nextVert_x >= 0 && cb->nextVert_x <= WIDTH && cb->nextVert_y >= 0 && cb->nextVert_y <= HEIGHT)
	{
		float	xVTocheck = 0.0;
		if (cb->left)
			xVTocheck = cb->nextVert_x - 1.0;
		else
			xVTocheck = cb->nextVert_x;
		float	yVTocheck = cb->nextVert_y;
		
		if (check_wall(cb ,xVTocheck, yVTocheck))
		{
			cb->VertW_x = cb->nextVert_x;
			cb->VertW_y = cb->nextVert_y;
			cb->found_vert = 1;
			break ;
		}
		else
		{
			cb->nextVert_x += cb->x_vstep;
			cb->nextVert_y += cb->y_vstep;
		}
	}
}

