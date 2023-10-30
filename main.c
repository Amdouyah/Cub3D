/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 08:56:40 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	castRay(t_cub *cb, int __unused r)
{
	float	main;
	float	wallheaight;
	float	ystart;
	float	yend;
	float	y_txt;
	float	x_txt;
	float	inc;

	get_angle_view(cb);
	get_horz(cb);
	get_vert(cb);
	main = 0;
	if (cb->found_horz)
		cb->dish = sqrt(pow(cb->horzw_x - cb->x_p, 2) + pow(cb->horzw_y
					- cb->y_p, 2));
	else
		cb->dish = 100000;
	if (cb->found_vert)
		cb->disv = sqrt(pow(cb->vertw_x - cb->x_p, 2) + pow(cb->vertw_y
					- cb->y_p, 2));
	else
		cb->disv = 100000;
	if (cb->dish >= cb->disv)
		main = cb->disv;
	else if (cb->disv > cb->dish)
		main = cb->dish;
	main *= cos(cb->rayangle - cb->view_p);
	wallheaight = 19500 / main;
	ystart = (HEIGHT / 2) - (wallheaight / 2);
	yend = ystart + wallheaight;
	y_txt = 0.0;
	x_txt = 0.0;
	inc = cb->no->height / wallheaight;
	while (ystart < yend)
	{
		if (ystart >= 0 && ystart < HEIGHT)
		{
			if (cb->dish >= cb->disv)
			{
				if (cos(cb->rayangle) > 0)
				{
					x_txt = get_position(cb->vertw_y, cb->ea->height);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->ea, x_txt,
								y_txt));
				}
				else if (cos(cb->rayangle) < 0)
				{
					x_txt = get_position(cb->vertw_y, cb->we->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->we, x_txt,
								y_txt));
				}
			}
			else
			{
				if (sin(cb->rayangle) > 0)
				{
					x_txt = get_position(cb->horzw_x, cb->so->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->so, x_txt,
								y_txt));
				}
				else if (sin(cb->rayangle) < 0)
				{
					x_txt = get_position(cb->horzw_x, cb->no->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->no, x_txt,
								y_txt));
				}
			}
		}
		y_txt += inc;
		ystart++;
	}
}

void	minimap(t_cub *cb)
{
	int		i;
	int		j;
	float	inc;

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
					cb->x_p = j * TILE_SIZE + 25;
					cb->y_p = i * TILE_SIZE + 25;
				}
			}
		}
	}
	i = 0;
	inc = rad(FOV) / WIDTH;
	cb->rayangle = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		castRay(cb, i);
		cb->rayangle += inc;
		i++;
	}
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
	cb->glo = &glo;
	cb->map = cb->glo->map.map;
	cb->x_p = -1;
	cb->y_p = -1;
	cb->no = mlx_load_png(cb->glo->no_path);
	cb->so = mlx_load_png(cb->glo->so_path);
	cb->we = mlx_load_png(cb->glo->we_path);
	cb->ea = mlx_load_png(cb->glo->ea_path);
	cb->view_p = 3 * (M_PI / 2);
	cb->rayangle = cb->view_p - rad(FOV / 2);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	minimap(cb);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);
}
