/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:21:41 by pamone            #+#    #+#             */
/*   Updated: 2023/07/28 20:00:27 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	*ch;
	unsigned char	target;

	ch = (unsigned char *) str;
	target = (unsigned char)c;
	while (*ch)
	{
		if (*ch == target)
			return ((char *)ch);
		ch++;
	}
	if (*ch == target)
		return ((char *)ch);
	return (0);
}
