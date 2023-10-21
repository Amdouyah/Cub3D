/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgannoun <bgannoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:54:07 by bgannoun          #+#    #+#             */
/*   Updated: 2022/10/17 12:26:01 by bgannoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("Hello");
// 	t_list *new;
// 		new = ft_lstnew("test");
// 	ft_lstadd_back(&no1, new);
// 	while (no1)
// 	{
// 		printf("%s\n", no1->content);
// 		no1 = no1->next;
// 	}
// }