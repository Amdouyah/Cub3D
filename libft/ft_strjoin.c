/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:53:03 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/17 18:15:14 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (len_s2 + len_s1 + 1));
	if (!res)
		return (0);
	i = 0;
	while (i != len_s1)
	{
		res[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (i != (len_s1 + len_s2))
		res[i++] = (char)s2[j++];
	res[(len_s1 + len_s2)] = '\0';
	return (res);
}
