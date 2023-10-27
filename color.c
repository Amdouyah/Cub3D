/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:33:22 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/27 16:34:20 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_ceil(t_cub *cb)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(cb->img, j,i, r_g_b(cb->glo->cling.red, cb->glo->cling.green, cb->glo->cling.blue, 255));
			j++;
		}
		i++;
	}
}

void ft_floor(t_cub *cb)
{
	int	i;
	int	j;

	i = HEIGHT / 2;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(cb->img, j,i, r_g_b(cb->glo->flor.red, cb->glo->flor.green, cb->glo->flor.blue, 255));
			j++;
		}
		i++;
	}
}

uint32_t	r_g_b(int r, int g, int b, int a)
{
	return (r << 26 | g << 16 | b << 8 | a);
}

uint32_t get_color(mlx_texture_t *png, uint32_t x, uint32_t y)
{
    if (png == NULL || png->pixels == NULL)
	{
        // Error handling: Check for NULL texture or NULL pixel data
        return 0;
    }
    if (x >= png->width || y >= png->height)
	{
        // Error handling: Check if (x, y) is within the image boundaries
        return 0;
    }
    // Calculate the offset to the pixel at (x, y)
    uint32_t pixelOffset = (y * png->width + x) * png->bytes_per_pixel;
    // Extract the color components
    uint8_t red = png->pixels[pixelOffset];
    uint8_t green = png->pixels[pixelOffset + 1];
    uint8_t blue = png->pixels[pixelOffset + 2];
    uint8_t alpha = png->pixels[pixelOffset + 3];

    // Create a 32-bit color value (assuming RGBA format)
    return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
