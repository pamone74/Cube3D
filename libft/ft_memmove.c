/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:59:40 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:23:15 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	char			*dst_ptr;
	const char		*src_ptr;

	dst_ptr = (char *)dest;
	src_ptr = (const char *)src;
	if (dst_ptr == src_ptr)
		return (dest);
	if (src_ptr < dst_ptr)
	{
		while (n--)
			dst_ptr[n] = src_ptr[n];
	}
	else
	{
		while (n--)
			*dst_ptr++ = *src_ptr++;
	}
	return (dest);
}
