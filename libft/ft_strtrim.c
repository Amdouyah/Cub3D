/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:04:18 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/19 21:25:10 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_checker(const char *set, const char str)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}

static int	index_ss(char const *str, char const *set)
{
	int	index_s;

	index_s = 0;
	while (str_checker(set, str[index_s]))
		index_s++;
	return (index_s);
}

static int	index_ff(char const *str, char const *set)
{
	int	index_f;

	index_f = ft_strlen(str) - 1;
	while (str_checker(set, str[index_f]))
		index_f--;
	return (index_f);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		index_s;
	int		index_f;
	int		set_len;
	int		i;
	char	*res;

	if (!str)
		return (0);
	index_s = index_ss(str, set);
	i = 0;
	index_f = index_ff(str, set);
	set_len = ft_strlen(set) - 1;
	if (index_s == (int)ft_strlen(str) && index_f == -1)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (index_f - index_s + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (index_s <= index_f)
		res[i++] = str[index_s++];
	res[i] = '\0';
	return (res);
}
