/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:19:11 by pamone            #+#    #+#             */
/*   Updated: 2023/07/28 20:06:16 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	*ch;
	unsigned char	target;

	ch = NULL;
	target = (unsigned char)c;
	if (target == '\0')
		return ((char *)str + ft_strlen(str));
	while (*str)
	{
		if (*str == target)
			ch = (unsigned char *)str;
		str++;
	}
	return ((char *)ch);
}
