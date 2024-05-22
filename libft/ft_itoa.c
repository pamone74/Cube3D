/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:26:56 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:20:48 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digits(int number)
{
	unsigned int	i;
	int				holder;

	i = 1;
	holder = number / 10;
	if (number < 0)
		holder = -holder;
	while (holder != 0)
	{
		holder /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	digits;
	long int		num;

	num = n;
	digits = count_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!(str))
		return (NULL);
	str[digits] = 0;
	while (digits--)
	{
		str[digits] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
