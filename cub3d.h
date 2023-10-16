/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:58:04 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/16 15:20:00 by amdouyah         ###   ########.fr       */
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
typedef struct s_cub{
	mlx_t* mlx;
	mlx_image_t* img;
	float x_p;
	float y_p;
	char **map;
	float xtmp;
	float ytmp;
	float view_p;
	float teta;
	float	angle;

	
}t_cub;


#endif