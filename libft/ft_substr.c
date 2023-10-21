/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:11:05 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/19 21:25:15 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;

	i = 0;
	if (s[0] == 0)
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s))
		res = malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	else
		res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (0);
	while (i < len && start <= (unsigned int)ft_strlen((char *)s))
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
