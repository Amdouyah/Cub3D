/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:59:39 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 21:10:00 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dbonus.h"

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

void	cast_ray(t_cub *cb, int __unused r)
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
	cb->rayangle = cb->view_p - rad(FOV / 2);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
}
