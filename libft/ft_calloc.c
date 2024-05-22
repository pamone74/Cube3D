/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:10:26 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:18:51 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*memory;

	total_size = num_elements * element_size;
	memory = malloc (total_size);
	if (memory != NULL)
	{
		ft_memset(memory, 0, total_size);
	}
	return (memory);
}
