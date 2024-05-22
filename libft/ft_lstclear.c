/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:44:27 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:20:57 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		next = node -> next;
		ft_lstdelone(node, del);
		node = next;
	}
	*lst = NULL;
}
