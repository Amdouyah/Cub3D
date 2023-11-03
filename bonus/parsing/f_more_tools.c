/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_more_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:49:59 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 22:43:43 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3dbonus.h"

void	reding_file_s(t_info *glo, char *name)
{
	glo->fd = open(name, O_RDONLY);
	if (glo->fd == -1)
	{
		error("Error opening the map\n");
		exit(1);
	}
}

void	is_end_cub(char *name)
{
	if (!ft_strnstr(name, "cub", ft_strlen(name)))
	{
		error("map must end with .cub\n");
		exit(1);
	}
}

int	get_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**find_ones(char **map, int rows, char *to_find)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (ft_strnstr(map[i], to_find, ft_strlen(map[i])))
			return (&map[i]);
		i++;
	}
	return (NULL);
}

void	skeep_space(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}
