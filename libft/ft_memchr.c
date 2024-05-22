/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:24:39 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:21:41 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char		*converted;
	size_t					i;

	converted = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (converted[i] == (unsigned char)c)
			return ((void *)(converted + i));
		i++;
	}
	return (NULL);
}
