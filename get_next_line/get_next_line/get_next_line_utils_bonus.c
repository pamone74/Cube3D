/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:47:57 by pamone            #+#    #+#             */
/*   Updated: 2023/08/19 17:16:13 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_line(char *remain_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!remain_str[i])
		return (NULL);
	while (remain_str[i] && remain_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (remain_str[i] && remain_str[i] != '\n')
	{
		str[i] = remain_str[i];
		i++;
	}
	if (remain_str[i] == '\n')
	{
		str[i] = remain_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_next_remain_str(char *remain_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remain_str[i] && remain_str[i] != '\n')
		i++;
	if (!remain_str[i])
	{
		free(remain_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(remain_str) - i + 1));
	if (!str)
	{
		free(remain_str);
		return (NULL);
	}
	i++;
	j = 0;
	while (remain_str[i])
		str[j++] = remain_str[i++];
	str[j] = '\0';
	free(remain_str);
	return (str);
}
