/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:06:15 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/31 19:58:23 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_line_tx(t_info *glo, int *count_tx, int i, char *tx)
{
	filling(glo->file[i]);
	if (!ft_strcmp(tx, "n"))
		glo->no = ft_split(glo->file[i], ' ');
	else if (!ft_strcmp(tx, "s"))
		glo->so = ft_split(glo->file[i], ' ');
	else if (!ft_strcmp(tx, "w"))
		glo->we = ft_split(glo->file[i], ' ');
	else if (!ft_strcmp(tx, "e"))
		glo->ea = ft_split(glo->file[i], ' ');
	(*count_tx)++;
}

void	fill_line_cl(t_info *glo, int *count_cl, int i, char *cl)
{
	if (!ft_strcmp(cl, "f"))
		glo->map.flor = glo->file[i];
	else if (!ft_strcmp(cl, "c"))
		glo->map.ciling = glo->file[i];
	(*count_cl)++;
}

void	get_map_info_s(t_info *glo, int *count_tx, int *count_cl, int i)
{
	if (ft_strnstr(glo->file[i], "NO", ft_strlen(glo->file[i])))
		fill_line_tx(glo, count_tx, i, "n");
	else if (ft_strnstr(glo->file[i], "SO", ft_strlen(glo->file[i])))
		fill_line_tx(glo, count_tx, i, "s");
	else if (ft_strnstr(glo->file[i], "WE", ft_strlen(glo->file[i])))
		fill_line_tx(glo, count_tx, i, "w");
	else if (ft_strnstr(glo->file[i], "EA", ft_strlen(glo->file[i])))
		fill_line_tx(glo, count_tx, i, "e");
	else if (ft_strnstr(glo->file[i], "F", ft_strlen(glo->file[i])))
		fill_line_cl(glo, count_cl, i, "f");
	else if (ft_strnstr(glo->file[i], "C", ft_strlen(glo->file[i])))
		fill_line_cl(glo, count_cl, i, "c");
	else
	{
		error("map errorrrrr\n");
		free_tx_tab(glo);
		free_table(glo->file);
		exit(1);
	}
}

void	get_map_info(t_info *glo)
{
	int	i;
	int	count_tx;
	int	count_cl;

	count_tx = 0;
	count_cl = 0;
	i = 0;
	while (glo->file[i]
		&& glo->file[i] != *find_ones(glo->file, get_rows(glo->file), "111"))
	{
		get_map_info_s(glo, &count_tx, &count_cl, i);
		i++;
	}
	checking_paths(glo, count_tx, count_cl);
	checking_colors(glo);
}

void	parsing(char *name, t_info *glo)
{
	while (*name == ' ' || *name == '\t')
		name++;
	is_end_cub(name);
	char *line = reading_file(glo, name);
	is_map_connected(line);
	
	glo->file = ft_split(line, '\n');
	free(line);
	get_map_info(glo);
}
