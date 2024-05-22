/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:49:41 by pamone            #+#    #+#             */
/*   Updated: 2023/07/26 17:46:58 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	const char	*srcc;
	char		*pp;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	srcc = src;
	pp = dest;
	while (n--)
	{
		pp[n] = srcc[n];
	}
	return (dest);
}
// int main()
// {
// 	char s[] = "Amone Patrick";
// 	ft_memcpy(s + 5, s + 6, 5);
// 	printf("the destination  now is: %s", s);
// }