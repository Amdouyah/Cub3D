/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:46:58 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/27 16:47:32 by amdouyah         ###   ########.fr       */
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

