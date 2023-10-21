/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:58:04 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/21 13:57:23 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
#define FOV 60
#define HEIGHT 900
#define WIDTH 1024
#define SPEED 3
#define TILE_SIZE 50

typedef struct s_cub{
	mlx_t*			mlx;
	mlx_image_t*	img;
	float			x_p;
	float			y_p;
	char			**map;
	float			xtmp;
	float			ytmp;
	float			view_p;
	float			rayAngle;
	float			distance;
	int				down;
	int				up;
	int				right;
	int				left;
	float			horzW_x;
	float			horzW_y;
	float			VertW_x; 
	float			VertW_y ;
	float			x_hstep;
	float			y_hstep;
	float			x_vstep;
	float			y_vstep;

}t_cub;


#endif