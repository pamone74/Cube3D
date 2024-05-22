/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:26:19 by pamone            #+#    #+#             */
/*   Updated: 2023/07/21 18:20:09 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int digit)
{
	int	return_value;

	return_value = 0;
	if (!(digit >= '0' && digit <= '9'))
		return_value = 0;
	else
		return_value = 1;
	return (return_value);
}
