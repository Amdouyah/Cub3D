/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainpast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:21:32 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/24 22:26:11 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_wall(t_cub *cb ,float x, float y)
{
  // Check if the x and y coordinates are within the bounds of the map.
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return (1);

  // Get the content of the map cell at the given coordinates.
  int index_x = (int)floor(x / TILE_SIZE);
  int index_y = (int)floor(y / TILE_SIZE);
  if (index_y >= 14)
    return (1);
	int len_y = ft_strlen(cb->map[index_y]);
  if (index_x >= len_y)
    return (1);
  char mapContent = cb->map[index_y][index_x];
  if (mapContent == '1')
	return (1);

  return (0);
}

// int check_wall(t_cub *cb, float x, float y)
// {
//   // Check if the x and y coordinates are within the bounds of the map.
// 	if ((int)y / TILE_SIZE < 7 
// 		&& (int)x / TILE_SIZE < 18
// 		&& cb->map[(int) y / TILE_SIZE][(int) x / TILE_SIZE] == '1')
// 		return (1);
// 	return (0);
// }

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
	while(++i < TILE_SIZE)
	{
		j = -1;
		while(++j < TILE_SIZE)
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
	while(i < 4)
	{
		j = -1;
		while(++j < 4)
			mlx_put_pixel(cb->img, j + y - 2, i + x - 2, rgb(255, 205, 75, 255));
		i++;
	}
}

void	dda(int xi, int yi, int xf, int yf, t_cub *map)
{
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
float	normlizeAngle(float angle)
{
	if (angle < 0)
        angle += (2 * M_PI);
    else
        angle = remainder(angle, 2 * M_PI);
    return (angle);
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
	if (found_horz)
		disH = sqrt(pow(cb->horzW_x - cb->x_p, 2) + pow(cb->horzW_y - cb->y_p, 2));
	else
		disH = 100000;
	if (found_vertical)
		disV = sqrt(pow(cb->VertW_x - cb->x_p, 2) + pow(cb->VertW_y - cb->y_p, 2));
	else
		disV = 100000;
	if (disH >= disV){
			dda(cb->x_p, cb->y_p, cb->VertW_x ,  cb->VertW_y , cb);
	}
	else if (disV > disH)
			dda(cb->x_p, cb->y_p, cb->horzW_x ,  cb->horzW_y , cb);
	// 	wallheaight = 72000 / disH;
	// float ystart = (HEIGHT / 2) - (wallheaight / 2);
	// float yend = ystart + wallheaight;
	// // printf("dis%f  Hei%f yst%f yen%f\n", dis, wallheaight, ystart, yend);
	// // exit(0);
	// // int x = ystart;
	// // x = abs(x);
	// while (ystart < yend){
	// 	// puts("hna");
	// 	if (ystart >= 0 && ystart < HEIGHT)
	// 		mlx_put_pixel(cb->img, r, ystart, rgb(241, 12,41,255));
	// 	ystart++;
	// 	// x++;
	// }
	  
	 
}
void	init_view(t_cub *cb, char c)
{
	if (c == 'N')
		cb->view_p = 3 * M_PI / 2;
	else if (c == 'W')
		cb->view_p =  M_PI;
	else if (c == 'E')
		cb->view_p =  0;
	else if (c == 'S')
		cb->view_p =  M_PI / 2;
}

void	minimap(t_cub *cb)
{
		
	int	i;
	int	j;

	i = -1;
	while(cb->map[++i])
	{
		j = -1;
		while(cb->map[i][++j])
		{
			if (cb->map[i][j] == '1')
				draw_squar(cb->img, i * TILE_SIZE, j * TILE_SIZE, rgb(255,0,0,128));
			else if (cb->map[i][j] == '0')
				draw_squar(cb->img, i * TILE_SIZE , j *TILE_SIZE, rgb(0,0,0,255));
			if (cb->map[i][j] == 'N' || cb->map[i][j] == 'S' || cb->map[i][j] == 'W' || cb->map[i][j] == 'E')
			{
				if (cb->x_p == -1 && cb->y_p == -1)
				{
					init_view(cb, cb->map[i][j]);
					cb->x_p = j * TILE_SIZE + 25;
					cb->y_p = i * TILE_SIZE + 25;
				}
				draw_squar(cb->img, i * TILE_SIZE, j * TILE_SIZE, rgb(0,0,0,255));
			}
		}
	}
	drawplayer(cb, cb->x_p, cb->y_p);
	i = 0;
	float inc = rad(FOV) / WIDTH;
	cb->rayAngle = cb->view_p - rad(FOV / 2);
	while (i < WIDTH)
	{
		castRay(cb, i);
		cb->rayAngle += inc;
		i++;
	}

}
void	ft_hook(void *p)
{
	t_cub *cb = p;
	
	// for(int i = 0 ; i < HEIGHT ; i++)
	// 	for(int j = 0; j < WIDTH; j++)
	// 		mlx_put_pixel(cb->img, j,i,rgb(0,0,0,255));
	cb->xtmp = cb->x_p ;
	cb->ytmp = cb->y_p ;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
	{
			cb->xtmp += cos(cb->view_p) * SPEED;
			cb->ytmp += sin(cb->view_p) * SPEED;
	}
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
	{
			cb->xtmp -= cos(cb->view_p + rad(90)) * SPEED;
			cb->ytmp -= sin(cb->view_p + rad(90)) * SPEED;
	}
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
	{	
			cb->xtmp -= cos(cb->view_p) * SPEED;
			cb->ytmp -= sin(cb->view_p) * SPEED;
	}
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
	{
			cb->xtmp += cos(cb->view_p + rad(90)) * SPEED;
			cb->ytmp += sin(cb->view_p + rad(90)) * SPEED;
	}
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
	{
		cb->view_p -= 0.05;
		if (cb->view_p >= 0)
			cb->view_p -= 2*M_PI;
		else if (cb->view_p < 2*M_PI)
			cb->view_p += 2*M_PI;
	}
	else if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
	{
		cb->view_p += 0.05;
		if (cb->view_p >= 0)
			cb->view_p -= 2 * M_PI;
		else if (cb->view_p < 2 * M_PI)
			cb->view_p += 2 * M_PI;
	}
	if ((cb->map[(int)(cb->y_p) / TILE_SIZE][(int)cb->xtmp / TILE_SIZE] != '1'
		&& cb->map[(int)(cb->ytmp)/TILE_SIZE][(int)cb->x_p/TILE_SIZE] != '1'
		&& cb->map[(int)cb->ytmp/TILE_SIZE][(int)(cb->xtmp) / TILE_SIZE] != '1'))
		{
			cb->x_p = cb->xtmp;
			cb->y_p = cb->ytmp;
			minimap(cb);
		}
}

int main(int ac, char **av )
{
	// int fd;	
	t_cub *cb;
	t_info glo;

	if (ac != 2)
		return (error("wrong number of arguments\n"));
	parsing(av[1], &glo);
	////

	cb = malloc(sizeof(t_cub));
	// cb->map = malloc(sizeof glo.map.map);
	cb->map = glo.map.map;
	// cb->map = malloc(sizeof(char *) * 8);

	// while(glo.map.map[i])
	// {
	// 	puts(glo.map.map[i]);
	// 	i++;
	// }
	// exit(0);
	
	// cb->map[0] = "111111111111111111";
	// cb->map[1] = "100000001000000001";
	// cb->map[2] = "100000100000110011";
	// cb->map[3] = "100000000000001001";
	// cb->map[4] = "100000000000000001";
	// cb->map[5] = "100N00000001110001";
	// cb->map[6] = "111111111111111111";
	// cb->map[7] = NULL;
	
	cb->x_p = -1;
	cb->y_p = -1;
	cb->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	cb->img = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->view_p = 3 * (M_PI/2);
	cb->rayAngle = cb->view_p - rad(FOV / 2);
	minimap(cb);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0); 
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);
	 
}
