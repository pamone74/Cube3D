/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:03:36 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:24:16 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen (str) + 1;
	cpy = (char *)malloc(len);
	if (!cpy)
		return (0);
	ft_strlcpy(cpy, str, len);
	return (cpy);
}
