/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:15:55 by pamone            #+#    #+#             */
/*   Updated: 2023/07/28 21:35:33 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	counter;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	counter = 0;
	if (dstsize - len == 0)
		return (len + ft_strlen(src));
	if (dstsize <= len)
		return (dstsize + ft_strlen(src));
	while (src[counter] && (len + counter + 1) < dstsize)
	{
		dst[len + counter] = src[counter];
		counter++;
	}
	dst[len + counter] = '\0';
	return (len + ft_strlen(src));
}
