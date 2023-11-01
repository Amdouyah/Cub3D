/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:58:04 by amdouyah          #+#    #+#             */
/*   Updated: 2023/11/01 17:06:39 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
// # include "/Users/bgannoun/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define FOV 60
# define HEIGHT 740
# define WIDTH 1150
# define SPEED 1
# define TILE_SIZE 20

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

typedef struct s_floats
{
	float	main;
	float	wallheaight;
	float	ystart;
	float	yend;
	float	y_txt;
	float	x_txt;
	float	inc;
}				t_floats;

typedef struct s_map
{
	char			*flor;
	char			*ciling;
	char			**map;
}					t_map;

typedef struct s_colors
{
	int				red;
	int				green;
	int				blue;
}					t_colors;

typedef struct s_info
{
	t_map			map;
	char			**file;
	int				fd;
	char			**no;
	char			**so;
	char			**we;
	char			**ea;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			**flor_table;
	char			**cling_table;
	t_colors		flor;
	t_colors		cling;
}					t_info;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	float			x_p;
	float			y_p;
	char			**map;
	float			xtmp;
	float			ytmp;
	float			view_p;
	float			rayangle;
	float			distance;
	float			horzw_x;
	float			horzw_y;
	float			vertw_x;
	float			vertw_y;
	float			nexthorz_x;
	float			nexthorz_y;
	float			nextvert_x;
	float			nextvert_y;
	float			x_hstep;
	float			y_hstep;
	float			x_vstep;
	float			y_vstep;
	int				right;
	int				down;
	int				up;
	int				left;
	int				found_horz;
	int				found_vert;
	float			dish;
	float			disv;
	t_info			*glo;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	int				x_mouse;
	int				y_mouse;
	int				y_mouse_tmp;
	int				x_mouse_tmp;
	float			ystart;
	float			yend;
	float			y_txt;
	float			x_txt;

}					t_cub;

void				skeep_space(char **str);
int					table_counter(char **table);
int					checking_inter(t_colors color);
int					is_found(char *str, char c);
void				filling(char *str);
void				free_table(char **tab);
void				free_tx_tab(t_info *glo);
void				free_cl_tab(t_info *glo);
int					error(char *str);
int					table_count(char **tab);
void				is_end_cub(char *name);
char				*reading_file(t_info *glo, char *name);
void				is_map_connected(char *map);
void				get_map_info(t_info *glo);
void				parsing(char *name, t_info *glo);
int					fill_color(t_info *glo);
void				checking_colors(t_info *glo);
void				is_path_valid(t_info *glo);
void				checking_paths(t_info *glo, int count_tx, int count_cl);
void				is_map_valid(t_info *glo);
int					isserroundind(char **map, int len);
int					checking_map(char **map);
int					get_rows(char **map);
char				**find_ones(char **map, int rows, char *to_find);
void				skeep_space(char **str);
int					ft_strcmp(char *s1, char *s2);
void				reding_file_s(t_info *glo, char *name);
void				is_end_cub(char *name);
char				*reading_file(t_info *glo, char *name);
int					checker(char *str);
/*raycast*/
int					check_wall(t_cub *cb, float x, float y);
void				get_horz(t_cub *cb);
void				get_horz2(t_cub *cb);
void				get_vert(t_cub *cb);
void				get_vert2(t_cub *cb);
void				get_vstep(t_cub *cb);
void				get_hsteps(t_cub *cb);
int					get_position(float ver, float width);
void				get_angle_view(t_cub *cb);
void				castray(t_cub *cb, int r);
/*draw*/
void				minimap(t_cub *cb);
void				sec_minimap(t_cub *cb);
void				drawplayer(t_cub *cb, int y, int x);
void				draw_squar(mlx_image_t *img, int y, int x,
						unsigned int color);
/*math*/
double				rad(float degree);
int					ft_abs(int n);
float				normlizeangle(float angle);
/*colors*/
uint32_t			r_g_b(int r, int g, int b, int a);
void				ft_floor(t_cub *cb);
void				ft_ceil(t_cub *cb);
uint32_t			get_color(mlx_texture_t *png, uint32_t x, uint32_t y);
/*hooks*/
void				ft_hook(void *p);
void				ft_up(t_cub *cb);
void				ft_down(t_cub *cb);
void				ft_left(t_cub *cb);
void				ft_right(t_cub *cb);
void				ft_mv_left(t_cub *cb);
void				ft_mv_right(t_cub *cb);
int					wall_check(t_cub *cb);
void				init_view(t_cub *cb, char c);

#endif