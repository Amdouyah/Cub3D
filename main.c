/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:00:02 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/30 07:00:26 by amdouyah         ###   ########.fr       */
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


void	castRay(t_cub *cb, int __unused  r)
{
	/*###################################*/
	/*###################################*/
	cb->rayAngle = normlizeAngle(cb->rayAngle);
	float h_down = 0;
	float h_right = 0;
	float h_up = 0;
	float h_left = 0;
	if (cb->rayAngle > 0 && cb->rayAngle < M_PI)
		h_down = 1;
	h_up = !h_down;
	h_right = 0;
	if (cb->rayAngle < 0.5 * M_PI  || cb->rayAngle >  1.5 * M_PI )
		h_right = 1;
	h_left = !h_right;
	
	float	x_Hintercept;
	float	y_Hintercept;
	int		found_horz;
	
	found_horz = 0;
	cb->horzW_x = 0;
	cb->horzW_y = 0;
	// int horsW_Content = 0;
	y_Hintercept = floor(cb->y_p / TILE_SIZE) * TILE_SIZE; 
	if (sin(cb->rayAngle) > 0)
		y_Hintercept += TILE_SIZE;
	x_Hintercept = (y_Hintercept - cb->y_p) / tan(cb->rayAngle);
	if (cos(cb->rayAngle) < 0)
		x_Hintercept = cb->x_p - fabs(x_Hintercept);
	else
		x_Hintercept = cb->x_p + fabs(x_Hintercept);
		
	cb->y_hstep = TILE_SIZE;
	if (sin(cb->rayAngle) < 0)
		cb->y_hstep *= -1;
	cb->x_hstep = TILE_SIZE / tan(cb->rayAngle);
	if ((cos(cb->rayAngle) < 0 && cb->x_hstep > 0)|| (cos(cb->rayAngle) > 0 && cb->x_hstep < 0))
		cb->x_hstep *= -1;
	float	nextHorz_x = x_Hintercept;
	float	nextHorz_y = y_Hintercept;
	if (sin(cb->rayAngle) < 0)
		nextHorz_y -= 0.001;
	while (nextHorz_x >= 0 && nextHorz_x <=WIDTH && nextHorz_y >= 0 && nextHorz_y <= HEIGHT)
	{
		float	xTocheck = nextHorz_x;
		float	yTocheck = nextHorz_y + (h_up ? -1 : 0);
		if (check_wall(cb , xTocheck, yTocheck))
		{
			cb->horzW_x = nextHorz_x;
			cb->horzW_y = nextHorz_y;
			// horsW_Content =  cb->map[(int)floor(yTocheck / TILE_SIZE)][(int)floor(xTocheck / TILE_SIZE)];
			found_horz = 1;
			break ;
		}
		else
		{
			nextHorz_x += cb->x_hstep;
			nextHorz_y += cb->y_hstep;
		}
	}
	// dda(cb->x_p, cb->y_p, cb->horzW_x ,  cb->horzW_y , cb);
	// printf("dx=%f  dy%f\n", fabs(dx), fabs(dy));
	/*###################################*/
	/*###################################*/
	/*vertical*/
	/*###################################*/
	/*###################################*/
	// printf("--->%f\n", cb->rayAngle);
	cb->rayAngle = normlizeAngle(cb->rayAngle);
	// float v_down = 0;
	float v_right = 0;
	// float v_up = 0;
	float v_left = 0;
	// if (cb->rayAngle > 0 && cb->rayAngle < M_PI)
	// 	v_down = 1;
	// v_up = !v_down;
	// v_right = 0;
	if (cb->rayAngle < M_PI / 2  || cb->rayAngle >  3 * M_PI / 2)
		v_right = 1;
	v_left = !v_right;
	int	found_vertical = 0;
	cb->VertW_x = 0;
	cb->VertW_y = 0;
	float	x_Vintercept; 
	float	y_Vintercept;
	// int vertW_Content = 0;
	x_Vintercept = floor(cb->x_p / TILE_SIZE) * TILE_SIZE; 
	if (cos(cb->rayAngle) > 0)
		x_Vintercept += TILE_SIZE;
	y_Vintercept = (x_Vintercept - cb->x_p) * tan(cb->rayAngle);
	
	if(sin(cb->rayAngle) > 0)
		y_Vintercept = cb->y_p + fabs(y_Vintercept);
	else
		y_Vintercept = cb->y_p - fabs(y_Vintercept);

	//calculate xstep && ystep 
	cb->x_vstep = TILE_SIZE;
	if (cos(cb->rayAngle) < 0)
		cb->x_vstep *= -1;
	
	cb->y_vstep = TILE_SIZE * tan(cb->rayAngle);   
	if ((sin(cb->rayAngle) > 0 && cb->y_vstep < 0)
		|| (sin(cb->rayAngle) < 0 && cb->y_vstep > 0))
		cb->y_vstep *= -1;
	
	float nextVert_x = x_Vintercept;
	float nextVert_y = y_Vintercept;
	found_vertical = 0;
	if (cos(cb->rayAngle) < 0)
		nextVert_x -= 0.001;
	while (nextVert_x >= 0 && nextVert_x <= WIDTH && nextVert_y >= 0 && nextVert_y <= HEIGHT)
	{
		float	xVTocheck = nextVert_x + (v_left ? -1 : 0);
		float	yVTocheck = nextVert_y;
		
		if (check_wall(cb ,xVTocheck, yVTocheck))
		{
			//find wall hit 
			cb->VertW_x = nextVert_x;
			cb->VertW_y = nextVert_y;
			// vertW_Content=  cb->map[(int)yVTocheck / TILE_SIZE][(int)xVTocheck / TILE_SIZE];
			found_vertical = 1;
			break ;
		}
		else
		{
			nextVert_x += cb->x_vstep;
			nextVert_y += cb->y_vstep;
		}
	}
	float disH;
	float disV;
	float main = 0;
	if (found_horz){
		disH = sqrt(pow(cb->horzW_x - cb->x_p, 2) + pow(cb->horzW_y - cb->y_p, 2));

	}
	else{
		disH = 100000;
	}
	if (found_vertical)
		disV = sqrt(pow(cb->VertW_x - cb->x_p, 2) + pow(cb->VertW_y - cb->y_p, 2));
	else
		disV = 100000;
	if (disH >= disV){
		main = disV;
			// dda(cb->x_p, cb->y_p, cb->VertW_x ,  cb->VertW_y , cb);
	}
	else if (disV > disH)
	{
		main = disH;
			// dda(cb->x_p, cb->y_p, cb->horzW_x ,  cb->horzW_y , cb);
	}
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
			if (disH >= disV){
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
