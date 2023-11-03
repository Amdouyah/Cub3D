/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/11/03 22:53:41 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

void	draw_minimap_con(t_cub *cb, int i, int j)
{
	if (cb->map[i][j] == '1')
		draw_sq(cb->img, i * TILE_S, j * TILE_S, r_g_b(255, 0, 0, 128));
	else if (cb->map[i][j] == '0')
		draw_sq(cb->img, i * TILE_S, j * TILE_S, r_g_b(0, 0, 0, 255));
}

void	draw_minimap(t_cub *cb)
{
	int	i;
	int	j;

	i = -1;
	while (cb->map[++i])
	{
		j = -1;
		while (cb->map[i][++j])
		{
			draw_minimap_con(cb, i, j);
			if (cb->map[i][j] == 'N' || cb->map[i][j] == 'S'
				|| cb->map[i][j] == 'W' || cb->map[i][j] == 'E')
			{
				if (cb->x_p == -1 && cb->y_p == -1)
				{
					init_view(cb, cb->map[i][j]);
					cb->x_p = j * TILE_S + (TILE_S / 2);
					cb->y_p = i * TILE_S + (TILE_S / 2);
				}
				draw_sq(cb->img, i * TILE_S, j * TILE_S, r_g_b(0, 0, 0, 255));
			}
		}
	}
}

void	sec_minimap(int i, t_cub *cb)
{
	float	inc;

	i = 0;
	inc = rad(FOV) / WIDTH;
	cb->rayangle = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		cast_ray(cb, i);
		cb->rayangle += inc;
		i++;
	}
	draw_minimap(cb);
	drawplayer(cb, cb->x_p, cb->y_p);
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
					cb->x_p = j * TILE_S + (TILE_S / 2);
					cb->y_p = i * TILE_S + (TILE_S / 2);
				}
			}
		}
	}
	sec_minimap(i, cb);
}

int	main(int ac, char **av)
{
	t_cub	*cb;
	t_info	glo;

	cb = NULL;
	if (ac != 2)
		return (error("wrong number of arguments\n"));
	parsing(av[1], &glo);
	cb = malloc(sizeof(t_cub));
	init_vars(cb, &glo);
	minimap(cb);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);
	mlx_delete_texture(cb->no);
	mlx_delete_texture(cb->ea);
	mlx_delete_texture(cb->we);
	mlx_delete_texture(cb->so);
	mlx_terminate(cb->mlx);
	free(cb);
}
