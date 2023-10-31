/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:07:52 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/31 20:33:42 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3dbonus.h"

char	*reading_file(t_info *glo, char *name)
{
	char	*line;
	char	*all;
	int		i;

	line = NULL;
	all = NULL;
	reding_file_s(glo, name);
	i = 0;
	while (1)
	{
		line = get_next_line(glo->fd);
		if (i == 0 && !line)
		{
			error("cub file is empty\n");
			free(line);
			exit(1);
		}
		if (!line)
			break ;
		all = join(all, line);
		if (line)
			free(line);
		i++;
	}
	close (glo->fd);
	free(line);
	return (all);
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
