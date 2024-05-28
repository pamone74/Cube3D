
 #include "get_next_line.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_get_line(char *remain_str)
// {
// 	int		i;
// 	char	*str_store;

// 	i = 0;
// 	while (remain_str[i] && remain_str[i] != '\n')
// 		i++;
// 	str_store = (char *)malloc(sizeof(char) * (i + 2));
// 	if (!str_store)
// 		return (NULL);
// 	i = 0;
// 	while (remain_str[i] && remain_str[i] != '\n')
// 	{
// 		str_store[i] = remain_str[i];
// 		i++;
// 	}
// 	if (remain_str[i] == '\n')
// 	{
// 		str_store[i] = remain_str[i];
// 		i++;
// 	}
// 	str_store[i] = '\0';
// 	return (str_store);
// }

// char	*ft_remain_str(char *remain_str)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	while (remain_str[i] && remain_str[i] != '\n')
// 		i++;
// 	if (!remain_str[i])
// 	{
// 		free(remain_str);
// 		return (NULL);
// 	}
// 	str = (char *)malloc(sizeof(char) * (ft_strlen(remain_str) - i + 1));
// 	if (!str)
// 		return (NULL);
// 	i++;
// 	j = 0;
// 	while (remain_str[i])
// 		str[j++] = remain_str[i++];
// 	str[j] = '\0';
// 	free(remain_str);
// 	return (str);
// }

// char	*ft_strjoin(char *remain_str, char *buff)
// {
// 	size_t	i;
// 	char	*str;
// 	size_t	j;

// 	if (!remain_str)
// 	{
// 		remain_str = (char *)malloc(sizeof(char) * 1);
// 		remain_str[0] = '\0';
// 	}
// 	if (!remain_str || !buff)
// 		return (NULL);
// 	str = malloc(sizeof(char) * strlen(remain_str) + strlen(buff) + 1);
// 	if (str == NULL)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	if (remain_str)
// 	{
// 		while (remain_str[++i] != '\0')
// 			str[i] = remain_str[i];
// 	}
// 	while (buff[j] != '\0')
// 		str[i++] = buff[j++];
// 	str[strlen(remain_str) + strlen(buff)] = '\0';
// 	free(remain_str);
// 	return (str);
// }

// char	*ft_strchr(char *str, int c)
// {
// 	if (!str)
// 		return (0);
// 	if (c == '\0')
// 		return ((char *) &str[strlen(str)]);
// 	while (*str)
// 	{
// 		if (*str == (char)c)
// 			return (str);
// 		str++;
// 	}
// 	return (0);
// }

//  char	*ft_read_remain_str(int fd, char *remain_str)
// {
// 	char	*buff;
// 	int		rd_bytes;

// 	buff = malloc((BUFFER_SIZE) * sizeof(char));
// 	if (!buff)
// 		return (NULL);
// 	rd_bytes = 1;
// 	rd_bytes = read(fd, buff, BUFFER_SIZE);
// 	while (!ft_strchr(remain_str, '\n') && rd_bytes != 0)
// 	{
// 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (rd_bytes == -1)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		buff[rd_bytes] = '\0';
// 		remain_str = ft_strjoin(remain_str, buff);
// 	}
// 	free(buff);
// 	return (remain_str);
// }
// // char	*ft_read_remain_str(int fd, char *remain_str)
// // {
// // 	char	*buff;
// // 	int		rd_bytes;

// // 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// // 	if (!buff)
// // 		return (NULL);

// // 	rd_bytes = read(fd, buff, BUFFER_SIZE);
// // 	if (rd_bytes == -1)
// // 	{
// // 		free(buff);
// // 		return (NULL);
// // 	}

// // 	buff[rd_bytes] = '\0';

// // 	while (!ft_strchr(remain_str, '\n') && rd_bytes != 0)
// // 	{
// // 		remain_str = ft_strjoin(remain_str, buff);
// // 		if (!remain_str)
// // 		{
// // 			free(buff);
// // 			return (NULL);
// // 		}

// // 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// // 		if (rd_bytes == -1)
// // 		{
// // 			free(buff);
// // 			free(remain_str);
// // 			return (NULL);
// // 		}

// // 		buff[rd_bytes] = '\0';
// // 	}

// // 	free(buff);
// // 	return (remain_str);
// // }
size_t	ft_strlen_get(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_get(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_get(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_get(char *left_str, char *buff)
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
	str = malloc(sizeof(char) * ((ft_strlen_get(left_str) + ft_strlen_get(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_get(left_str) + ft_strlen_get(buff)] = '\0';
	free(left_str);
	return (str);
}

char	*ft_get_line(char *left_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen_get(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}