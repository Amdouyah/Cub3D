/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:21:50 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/18 23:51:17 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*bs1;
	unsigned char	*bs2;

	bs1 = (unsigned char *)s1;
	bs2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (bs1[i] != bs2[i])
			return (bs1[i] - bs2[i]);
		i++;
	}
	return (0);
}
