/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:08:06 by pamone            #+#    #+#             */
/*   Updated: 2023/07/28 21:04:31 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*buffer_src;
	size_t		src_len;
	size_t		i;

	buffer_src = src;
	src_len = 0;
	i = 0;
	while (buffer_src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	if (size > 0)
	{
		while (i < size - 1 && buffer_src[i] != '\0')
		{
			dest[i] = buffer_src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}
