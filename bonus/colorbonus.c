/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:22 by amdouyah          #+#    #+#             */
/*   Updated: 2023/11/04 11:36:47 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	ft_ceil(t_cub *cb)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(cb->img, j, i, r_g_b(cb->glo->cling.red,
					cb->glo->cling.green, cb->glo->cling.blue, 255));
			j++;
		}
		i++;
	}
}

void	ft_floor(t_cub *cb)
{
	int	i;
	int	j;

	i = HEIGHT / 2;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(cb->img, j, i, r_g_b(cb->glo->flor.red,
					cb->glo->flor.green, cb->glo->flor.blue, 255));
			j++;
		}
		i++;
	}
}

uint32_t	r_g_b(int r, int g, int b, int a)
{
	return (r << 26 | g << 16 | b << 8 | a);
}

uint32_t	get_color(mlx_texture_t *png, uint32_t x, uint32_t y)
{
	uint32_t	pixeloffset;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;

	if (png == NULL || png->pixels == NULL)
		return (0);
	if (x >= png->width || y >= png->height)
		return (0);
	pixeloffset = (y * png->width + x) * png->bytes_per_pixel;
	red = png->pixels[pixeloffset];
	green = png->pixels[pixeloffset + 1];
	blue = png->pixels[pixeloffset + 2];
	alpha = png->pixels[pixeloffset + 3];
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
