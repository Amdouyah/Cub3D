/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 08:16:11 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_squar(mlx_image_t *img, int y, int x, unsigned int color)
{
	int	i;
	int	j;

	i = -1;  
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			mlx_put_pixel(img, j + x, i + y, color);
	}
}

void	drawplayer(t_cub *cb, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = -1;
		while (++j < 4)
			mlx_put_pixel(cb->img, j + y - 2, i + x - 2, r_g_b(255, 205, 75, 255));
		i++;
	}
}
int get_position(float ver, float width)
{
	
	int pos = ((ver / TILE_SIZE) - (int)ver/TILE_SIZE ) * width;
	return pos;
}
void	get_hsteps(t_cub *cb)
{
	cb->y_hstep = TILE_SIZE;
	if (sin(cb->rayAngle) < 0)
		cb->y_hstep *= -1;
	cb->x_hstep = TILE_SIZE / tan(cb->rayAngle);
	if ((cos(cb->rayAngle) < 0 && cb->x_hstep > 0)|| (cos(cb->rayAngle) > 0 && cb->x_hstep < 0))
		cb->x_hstep *= -1;
}

void	get_vstep(t_cub *cb)
{
	cb->x_vstep = TILE_SIZE;
	if (cos(cb->rayAngle) < 0)
		cb->x_vstep *= -1;
	cb->y_vstep = TILE_SIZE * tan(cb->rayAngle);   
	if ((sin(cb->rayAngle) > 0 && cb->y_vstep < 0)
		|| (sin(cb->rayAngle) < 0 && cb->y_vstep > 0))
		cb->y_vstep *= -1;
}

void	get_angle_view(t_cub *cb)
{
	cb->rayAngle = normlizeAngle(cb->rayAngle);
	cb->down = 0;
	cb->right = 0;
	cb->up = 0;
	cb->left = 0;
	if (cb->rayAngle > 0 && cb->rayAngle < M_PI)
		cb->down = 1;
	cb->up = !cb->down;
	cb->right = 0;
	if (cb->rayAngle < 0.5 * M_PI  || cb->rayAngle >  1.5 * M_PI )
		cb->right = 1;
	cb->left = !cb->right;
}

void	castRay(t_cub *cb, int __unused  r)
{
	float	main;
	get_angle_view(cb);
	get_horz(cb);
	get_vert(cb);
	
	main = 0;
	if (cb->found_horz)
		cb->disH = sqrt(pow(cb->horzW_x - cb->x_p, 2) + pow(cb->horzW_y - cb->y_p, 2));
	else
		cb->disH = 100000;
	if (cb->found_vert)
		cb->disV = sqrt(pow(cb->VertW_x - cb->x_p, 2) + pow(cb->VertW_y - cb->y_p, 2));
	else
		cb->disV = 100000;
	if (cb->disH >= cb->disV)
		main = cb->disV;
	else if (cb->disV > cb->disH)
		main = cb->disH;
	main *=   cos(cb->rayAngle - cb->view_p);
	float wallheaight = 19500 / main;
	float ystart = (HEIGHT / 2) - (wallheaight / 2);
	float yend = ystart + wallheaight;
	float y_txt = 0.0;
	float x_txt = 0.0;
	float inc = cb->no->height / wallheaight;
	
	while (ystart < yend)
	{
		if (ystart >= 0 && ystart < HEIGHT )
		{
			if (cb->disH >= cb->disV){
				if (cos(cb->rayAngle) > 0){
					x_txt = get_position(cb->VertW_y, cb->ea->height);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->ea, x_txt, y_txt));
				}
				else if (cos(cb->rayAngle) < 0){
					x_txt = get_position(cb->VertW_y, cb->we->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->we, x_txt, y_txt));
				}

			}
			else {
				if (sin(cb->rayAngle) > 0)
				{
					x_txt = get_position(cb->horzW_x, cb->so->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->so, x_txt, y_txt));
				}
				else if (sin(cb->rayAngle) < 0)
				{
					x_txt = get_position(cb->horzW_x, cb->no->width);
					mlx_put_pixel(cb->img, r, ystart, get_color(cb->no, x_txt, y_txt));
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
	while(cb->map[++i])
	{
		j = -1;
		while(cb->map[i][++j])
		{
			if (cb->map[i][j] == 'N' || cb->map[i][j] == 'S' || cb->map[i][j] == 'W' || cb->map[i][j] == 'E')
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
	cb->rayAngle = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		castRay(cb, i);
		cb->rayAngle += inc;
		i++;
	}
}

int main(int ac, char **av )
{
	t_cub *cb = NULL;
	t_info glo;

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
	cb->view_p = 3 * (M_PI/2);
	cb->rayAngle = cb->view_p - rad(FOV / 2);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	minimap(cb);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0); 
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);	 
}
