/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdouyah <amdouyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:14:06 by bgannoun          #+#    #+#             */
/*   Updated: 2023/11/03 22:11:07 by amdouyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	is_map_valid(t_info *glo)
{
	glo->map.map = find_ones(glo->file, get_rows(glo->file), "111");
	if (!glo->map.map || checking_map(glo->map.map))
	{
		error("map error\n");
		exit(1);
	}
}

int	isserroundind(char **map, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || i == len - 1 || j == 0
					|| j == (int)ft_strlen(map[i]) - 1)
					return (1);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	is_map_connected(char *map)
{
	char	*two_lines;
	char	*ptr;
	int		i;

	ptr = ft_strnstr(map, "111", ft_strlen(map));
	two_lines = NULL;
	if (ptr)
		two_lines = ft_strnstr(ptr, "\n\n", ft_strlen(map));
	i = 0;
	if (two_lines)
	{
		while (two_lines[i])
		{
			if (two_lines[i++] != '\n')
			{
				exit(1);
			}
		}
	}
}

int	checking_map_s(char **map, int i, int j, int *count_p)
{
	if (map[i][j] == '0')
	{
		if (j > (int)ft_strlen(map[i - 1]) - 1
			|| j > (int)ft_strlen(map[i + 1]) - 1)
			return (1);
	}
	if (map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'E' || map[i][j] == 'W')
	{
		if (i == 0 || i == table_counter(map) - 1
			|| j == 0 || j == (int)ft_strlen(map[i]) - 1)
			return (1);
		(*count_p)++;
	}
	if (map[i][j] && map[i][j] != '0' && map[i][j] != '1'
		&& map[i][j] != 'N' && map[i][j] != 'S'
		&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != ' ')
		return (1);
	return (0);
}

int	checking_map(char **map)
{
	int	i;
	int	j;
	int	count_p;

	count_p = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && !map[i +1])
				return (1);
			if (checking_map_s(map, i, j, &count_p))
				return (1);
			j++;
		}
		i++;
	}
	if (count_p != 1 || isserroundind(map, table_counter(map)))
		return (1);
	return (0); 
}
