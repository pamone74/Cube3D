/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:15:33 by pamone            #+#    #+#             */
/*   Updated: 2023/08/19 18:03:06 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_remain_str(int fd, char *remain_str)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(remain_str, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		remain_str = ft_strjoin(remain_str, buffer);
	}
	free(buffer);
	return (remain_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remain_str[256];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	remain_str[fd] = ft_read_to_remain_str(fd, remain_str[fd]);
	if (!remain_str[fd])
		return (NULL);
	line = ft_line(remain_str[fd]);
	remain_str[fd] = ft_next_remain_str(remain_str[fd]);
	return (line);
}
