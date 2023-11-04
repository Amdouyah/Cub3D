/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:07:52 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/04 11:30:51 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*reading_file(t_info *glo, char *name)
{
	int		i;

	glo->line = NULL;
	glo->all = NULL;
	reding_file_s(glo, name);
	i = 0;
	while (1)
	{
		glo->line = get_next_line(glo->fd);
		if (i == 0 && !glo->line)
		{
			error("cub file is empty\n");
			free(glo->line);
			exit(1);
		}
		if (!glo->line)
			break ;
		glo->all = join(glo->all, glo->line);
		if (glo->line)
			free(glo->line);
		i++;
	}
	close (glo->fd);
	free(glo->line);
	return (glo->all);
}

int	checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

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

void	fill_line_tx_con(t_info *glo, char *tx, int i)
{
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
}

void	fill_line_tx(t_info *glo, int *count_tx, int i, char *tx)
{
	filling(glo->file[i]);
	fill_line_tx_con(glo, tx, i);
	(*count_tx)++;
}
