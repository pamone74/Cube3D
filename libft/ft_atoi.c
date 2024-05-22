/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:04:53 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 21:15:17 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * ft_whitespace(const char **str) is for checking the white spaces
 * ft_sign
*/
static void	ft_whitespace(const char **str)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
}

static int	ft_sign(const char **str)
{
	int	sign;

	sign = 1;
	ft_whitespace(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	digit;

	result = 0;
	sign = ft_sign(&str);
	while (*str && (*str >= '0' && *str <= '9'))
	{
		digit = *str - '0';
		if (result > 2147483647 / 10 && (result == 2147483647 / 10 && 
				digit > 2147483647 % 10))
		{
			if (sign == 1)
				return (2147483647);
			else
				return (-2147483648);
		}
		result = result * 10 + digit;
		str++;
	}
	return (sign * result);
}



/*
This Atoi is modified to handle the int overflow by retunrning -1 and 1

*/


// int	ft_atoi_handle_overflow(const char *str)
// {
// 	int	sign;
// 	long long	result;
// 	int	digit;

// 	result = 0;
// 	sign = ft_sign(&str);
// 	while (*str && (*str >= '0' && *str <= '9'))
// 	{
// 		digit = *str - '0';
// 		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && 
// 				digit > LLONG_MAX % 10))
// 		{
// 			if (sign == 1 || sign == -1)
// 			{
// 				ft_pustr("Invalid Input");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		result = result * 10 + digit;
// 		str++;
// 	}
// 	return (sign * result);
// }
