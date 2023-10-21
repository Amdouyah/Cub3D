/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:22:17 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/11 19:40:39 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	strlenn(char *ch)
{
	size_t	i;

	i = 0;
	if (!ch)
		return (0);
	while (ch[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != (char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (&str[i]);
}

char	*join(char *s1, char *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	len_s1 = strlenn(s1);
	len_s2 = strlenn(s2);
	res = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i != len_s1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (i != (len_s1 + len_s2))
		res[i++] = s2[j++];
	res[(len_s1 + len_s2)] = '\0';
	free(s1);
	return (res);
}

char	*cut_first(char *out)
{
	int		i;
	char	*line;

	i = 0;
	while (out[i] && out[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (out[i] != '\0' && out[i] != '\n')
	{
		line[i] = out[i];
		i++;
	}
	if (out[i] && out[i] == '\n')
	{
		line[i] = out[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*cut_last(char *out)
{
	char	*reserve;
	int		i;
	int		j;
	int		count;

	i = 0;
	while (out[i] && out[i] != '\n')
		i++;
	if (out[i] == '\n')
		i++;
	if (out[i] == '\0')
	{
		free(out);
		return (NULL);
	}
	count = strlenn(ft_strchr(out, '\n')) - 1;
	reserve = malloc(sizeof(char) * count + 1);
	j = 0;
	while (out[i])
		reserve[j++] = out[i++];
	reserve[j] = '\0';
	free(out);
	return (reserve);
}
