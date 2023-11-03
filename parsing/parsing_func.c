/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:07:52 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 22:09:02 by amdouyah         ###   ########.fr       */
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
