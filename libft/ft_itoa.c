/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:12:17 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/19 01:37:18 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*return_v(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (0);
}

char	*ft_itoa(int n)
{
	int		l;
	int		int_l;
	char	*res;

	l = int_count(n) - 1;
	int_l = int_count(n);
	if (n == 0 || n == -2147483648)
		return (return_v(n));
	res = (char *)malloc(sizeof(char) * (int_count(n) + 1));
	if (!res)
		return (0);
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		res[l--] = (n % 10) + '0';
		n = n / 10;
	}
	res[int_l] = '\0';
	return (res);
}
