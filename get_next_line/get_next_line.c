/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:04:54 by bgannoun          #+#    #+#             */
/*   Updated: 2023/10/11 20:29:19 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_n(char *ch)
{
	int	i;

	i = 0;
	while (ch[i])
	{
		if (ch[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_to_out(int fd, char *buf, char *out)
{
	int	j;

	j = 1;
	while (1)
	{
		j = read(fd, buf, BUFFER_SIZE);
		if (j == -1)
		{
			free(out);
			free(buf);
			out = NULL;
			return (out);
		}
		if (j <= 0)
			break ;
		buf[j] = '\0';
		out = join(out, buf);
		if (check_n(out))
			break ;
	}
	free(buf);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*out;
	char		*line;
	char		*buf;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	out = read_to_out(fd, buf, out);
	if (!out)
		return (NULL);
	line = cut_first(out);
	out = cut_last(out);
	return (line);
}
