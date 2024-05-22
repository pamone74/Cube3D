/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:20:29 by pamone            #+#    #+#             */
/*   Updated: 2023/07/19 18:13:00 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (new == NULL)
		return ;
	if (*lst)
	{
		node = *lst;
		while (node ->next != NULL)
		{
			node = node -> next;
		}
		node->next = new;
	}
	else
		*lst = new;
}
