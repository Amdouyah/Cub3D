/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:06:15 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/04 11:15:33 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_leaks_tx(int count)
{
	if (count < 1)
		return ;
	else
	{
		error("tx error\n");
		exit(1);
	}
}

void	fill_line_tx(t_info *glo, int *count_tx, int i, char *tx)
{
	filling(glo->file[i]);
	if (!ft_strcmp(tx, "n"))
	{
		check_leaks_tx(glo->nn);
		glo->no = ft_split(glo->file[i], ' ');
		glo->nn++;
	}
	else if (!ft_strcmp(tx, "s"))
	{
		check_leaks_tx(glo->ss);
		glo->so = ft_split(glo->file[i], ' ');
		glo->ss++;
	}
	else if (!ft_strcmp(tx, "w"))
	{
		check_leaks_tx(glo->ww);
		glo->we = ft_split(glo->file[i], ' ');
		glo->ww++;
	}
	else if (!ft_strcmp(tx, "e"))
	{
		check_leaks_tx(glo->ee);
		glo->ea = ft_split(glo->file[i], ' ');
		glo->ee++;
	}
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
		exit(1);
	}
}

void	get_map_info(t_info *glo)
{
	int		i;
	int		count_tx;
	int		count_cl;
	char	**ptr;

	count_tx = 0;
	count_cl = 0;
	glo->nn = 0;
	glo->ss = 0;
	glo->ww = 0;
	glo->ee = 0;
	i = 0;
	ptr = find_ones(glo->file, get_rows(glo->file), "111");
	if (!ptr)
	{
		error("map errorrrrr\n");
		exit(1);
	}
	while (glo->file[i]
		&& glo->file[i] != *ptr)
	{
		get_map_info_s(glo, &count_tx, &count_cl, i);
		i++;
	}
	checking_paths(glo, count_tx, count_cl);
	checking_colors(glo);
}

void	parsing(char *name, t_info *glo)
{
	char	*line;

	line = NULL;
	while (*name == ' ' || *name == '\t')
		name++;
	is_end_cub(name);
	line = reading_file(glo, name);
	is_map_connected(line);
	glo->file = ft_split(line, '\n');
	free(line);
	get_map_info(glo);
}
