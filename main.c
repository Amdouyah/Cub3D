/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/11/03 22:45:20 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays(t_cub *cb, t_floats *vars)
{
	get_angle_view(cb);
	get_horz(cb);
	get_vert(cb);
	vars->main = 0;
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
		vars->main = cb->disv;
	else if (cb->disv > cb->dish)
		vars->main = cb->dish;
	vars->main *= cos(cb->rayangle - cb->view_p);
	vars->wallheaight = 19500 / vars->main;
	vars->ystart = (HEIGHT / 2) - (vars->wallheaight / 2);
	vars->yend = vars->ystart + vars->wallheaight;
	vars->y_txt = 0.0;
	vars->x_txt = 0.0;
	vars->inc = cb->no->height / vars->wallheaight;
}

void	draw_rays(int r, t_cub *cb, t_floats *vars)
{
	vars->x_txt = get_position(cb->vertw_y, cb->ea->height);
	if (cos(cb->rayangle) > 0)
		mlx_put_pixel(cb->img, r, vars->ystart, get_color(cb->ea, vars->x_txt,
				vars->y_txt));
	else if (cos(cb->rayangle) < 0)
		mlx_put_pixel(cb->img, r, vars->ystart, get_color(cb->we, vars->x_txt,
				vars->y_txt));
}

void	castray(t_cub *cb, int r)
{
	t_floats	vars;

	init_rays(cb, &vars);
	while (vars.ystart < vars.yend)
	{
		if (vars.ystart >= 0 && vars.ystart < HEIGHT)
		{
			if (cb->dish >= cb->disv)
				draw_rays(r, cb, &vars);
			else
			{
				vars.x_txt = get_position(cb->horzw_x, cb->so->width);
				if (sin(cb->rayangle) > 0)
					mlx_put_pixel(cb->img, r, vars.ystart,
						get_color(cb->so, vars.x_txt, vars.y_txt));
				else if (sin(cb->rayangle) < 0)
					mlx_put_pixel(cb->img, r, vars.ystart,
						get_color(cb->no, vars.x_txt, vars.y_txt));
			}
		}
		vars.y_txt += vars.inc;
		vars.ystart++;
	}
}

void	init_vars(t_cub *cb, t_info *glo)
{
	cb->glo = glo;
	cb->map = cb->glo->map.map;
	cb->x_p = -1;
	cb->y_p = -1;
	cb->x_mouse = 0;
	cb->y_mouse = 0;
	cb->no = mlx_load_png(cb->glo->no_path);
	cb->so = mlx_load_png(cb->glo->so_path);
	cb->we = mlx_load_png(cb->glo->we_path);
	cb->ea = mlx_load_png(cb->glo->ea_path);
	if (!cb->no || !cb->so || !cb->we || !cb->ea)
	{
		printf("tx error\n");
		exit(1);
	}
	cb->rayangle = cb->view_p - rad(FOV / 2);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
}

int	main(int ac, char **av)
{
	t_cub	*cb;
	t_info	glo;

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
