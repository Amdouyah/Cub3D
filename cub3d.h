/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:58:04 by amdouyah          #+#    #+#             */
/*   Updated: 2023/10/24 17:05:46 by amdouyah         ###   ########.fr       */
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
#define HEIGHT 740
#define WIDTH 1150
#define SPEED 1
#define TILE_SIZE 20

///
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_map
{
	char	*flor;
	char	*ciling;
	char	**map;
}				t_map;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}				t_colors;

typedef struct s_info
{
	t_map		map;
	char		**file;
	int			fd;
	char		**no;
	char		**so;
	char		**we;
	char		**ea;
	char		*no_path; 
	char		*so_path;
	char		*we_path;
	char		*ea_path;	
	char		**flor_table;
	char		**cling_table;
	t_colors	flor;
	t_colors	cling;
}				t_info;

void	skeep_space(char **str);
int		table_counter(char **table);
int		checking_inter(t_colors color);
int		is_found(char *str, char c);
void	filling(char *str);
void	free_table(char **tab);
void	free_tx_tab(t_info *glo);
void	free_cl_tab(t_info *glo);
int		error(char *str);
int		table_count(char **tab);
void	is_end_cub(char *name);
char	*reading_file(t_info *glo, char *name);
void	is_map_connected(char *map);
void	get_map_info(t_info *glo);
void	parsing(char *name, t_info *glo);
int		fill_color(t_info *glo);
void	checking_colors(t_info *glo);
void	is_path_valid(t_info *glo);
void	checking_paths(t_info *glo, int count_tx, int count_cl);
void	is_map_valid(t_info *glo);
int		isserroundind(char **map, int len);
int		checking_map(char **map);
int		get_rows(char **map);
char	**find_ones(char **map, int rows, char *to_find);
void	skeep_space(char **str);
int		ft_strcmp(char *s1, char *s2);
void	reding_file_s(t_info *glo, char *name);
void	is_end_cub(char *name);
char	*reading_file(t_info *glo, char *name);
int		checker(char *str);

///

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
	t_info 			*glo;

}t_cub;


#endif