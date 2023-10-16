/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/16 15:50:09 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
double rad(float degree)
{
	return (degree * M_PI / 180);
}
void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c; 
}

int abs(int n)
{ 
	if (n < 0)
		return (n * (-1));
	return (n);
}

void	draw_squar(mlx_image_t *img, int y, int x, unsigned int color)
{
	int	i;
	int j;

	i = -1;
	while(++i < 50)
	{
		j = -1;
		while(++j < 50)
			mlx_put_pixel(img, j + x, i + y, color);
	}
}
uint32_t rgb(int r, int g, int b, int a)
{
	return (r << 26 | g << 16 | b << 8 | a);
}

void	drawplayer(t_cub *cb, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while(i < 6)
	{
		j = -1;
		while(++j < 6)
			mlx_put_pixel(cb->img, j + y - 3, i + x - 3, rgb(255, 205, 75, 255));
		i++;
	}
}

void	dda(int xi, int yi, int xf, int yf, t_cub *map)
{
	// t_data	p;
	int dy,dx;
	float yinc,xinc;
	int steps;
	float	x;
	float	y;

	dy = yf - yi;
	dx = xf - xi;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else 
		steps = abs(dy);
	yinc = dy / (float)steps; //point to point in x
	xinc = dx / (float)steps;
	x = xi;
	y = yi;
	while (steps)
	{
		mlx_put_pixel(map->img, x, y, rgb(255,255,255,255));
		x += xinc;
		y += yinc;
		steps--;
	}
}

void minimap(t_cub *cb)
{
		
	int i = -1;
	int j;
	while(cb->map[++i])
	{
		j = -1;
		while(cb->map[i][++j])
		{
			if (cb->map[i][j] == '1')
				draw_squar(cb->img, i * 50, j * 50, rgb(255,0,0,128));
			else if (cb->map[i][j] == '0')
				draw_squar(cb->img, i * 50 , j *50, rgb(0,0,0,255));
			else if (cb->map[i][j] == 'N')
			{
				if (cb->x_p == -1 && cb->y_p == -1)
				{
					cb->x_p = j * 50 + 25;
					cb->y_p = i * 50 + 25;	
				}
				draw_squar(cb->img, i * 50, j * 50, rgb(0,0,0,255));
			}
		}
	}
	drawplayer(cb, cb->x_p, cb->y_p);
	i = 0;
	float yf, xf;
	float inc = rad(FOV) / WIDTH;
	cb->teta = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		yf = sin(cb->teta) * 50;
		xf = cos(cb->teta) * 50;
		dda(cb->x_p, cb->y_p, xf + cb->x_p, yf + cb->y_p, cb);
		cb->teta += inc;
		i++;
	}
	
	// cb->teta = cb->view_p - rad(FOV / 2) + cb->angle;
	// printf("%f-------%f\n", cb->teta, rad(0));
	// for (int i = 0; i < WIDTH;i++)
	// {	
	// 	cb->teta += rad(FOV) / WIDTH;
	// }
	// dda(cb->x_p, cb->y_p, xf + cb->x_p + 15, yf + cb->y_p, cb);
	// dda(cb->x_p, cb->y_p, xf + cb->x_p + 30, yf + cb->y_p, cb);
	// dda(cb->x_p, cb->y_p, xf + cb->x_p + 45, yf + cb->y_p, cb);

}
void	ft_hook(void *p)
{
	t_cub *cb = p;
	
	// cp_cb = cb;
	cb->xtmp = cb->x_p ;
	cb->ytmp = cb->y_p ;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
	{
			cb->xtmp += cos(cb->view_p) * SPEED;
			cb->ytmp += sin(cb->view_p) * SPEED;
	}
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
	{
			cb->xtmp -= cos(cb->view_p + rad(90)) * SPEED;
			cb->ytmp -= sin(cb->view_p + rad(90)) * SPEED;
	}
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
	{	
			cb->xtmp -= cos(cb->view_p) * SPEED;
			cb->ytmp -= sin(cb->view_p) * SPEED;
	}
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
	{
			cb->xtmp += cos(cb->view_p + rad(90)) * SPEED;
			cb->ytmp += sin(cb->view_p + rad(90)) * SPEED;
	}
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
	{
		cb->view_p -= 0.05;
		if (cb->view_p >= 0)
			cb->view_p -= 2*M_PI;
		else if (cb->view_p < 2*M_PI)
			cb->view_p += 2*M_PI;
	}
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
	{
		cb->view_p += 0.05;
		if (cb->view_p >= 0)
			cb->view_p -= 2*M_PI;
		else if (cb->view_p < 2*M_PI)
			cb->view_p += 2*M_PI;
	}
	if ((cb->map[(int)(cb->ytmp + (SPEED / 2)) / 50][(int)cb->xtmp / 50] != '1'
		|| cb->map[(int)(cb->ytmp - (SPEED /2))/50][(int)cb->xtmp/50] != '1'
		|| cb->map[(int)cb->ytmp/50][(int)(cb->xtmp - (SPEED / 2) ) / 50] != '1'
		|| cb->map[(int)cb->ytmp/50][(int)(cb->xtmp + (SPEED / 2))/50] != '1'))
		{
			cb->x_p = cb->xtmp;
			cb->y_p = cb->ytmp;
			minimap(cb);
		}		
}
/*
yp & xp 
if yp || xp !1 
y1 = yp + ky 
x1 = xp
*/

int main()
{
	// int fd;
	t_cub *cb;	

	cb = malloc(sizeof(t_cub));
	cb->map = malloc(sizeof(char *) * 8);
	
	cb->map[0] = "111111111111111111";
	cb->map[1] = "100000001000000001";
	cb->map[2] = "101010100000110011";
	cb->map[3] = "100000000000001001";
	cb->map[4] = "1000100N0000000001";
	cb->map[5] = "100000000001110001";
	cb->map[6] = "111111111111111111";
	cb->map[7] = NULL;
	// int color;
	// mlx_is_key_down(mlx, MLX_KEY_W);
	
	cb->x_p = -1;
	cb->y_p = -1;
	// cb->angle = 0;
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->view_p = 3 * (M_PI / 2);
	cb->teta = cb->view_p - rad(FOV / 2);
	minimap(cb);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0); 
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);
	 
}

