/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:15:52 by pamone            #+#    #+#             */
/*   Updated: 2023/07/27 19:41:28 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*temp;
	char			*temp_start;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (temp == NULL)
		return (NULL);
	temp_start = temp;
	while (*s1 != '\0')
		*temp++ = *s1++;
	while (*s2 != '\0')
		*temp++ = *s2++;
	*temp = '\0';
	return (temp_start);
}
// int main()
// {
// 	char s[] = "42";
// 	char d[] = "Abu dhabi";
// 	printf("%s",ft_strjoin(s, d));
// }