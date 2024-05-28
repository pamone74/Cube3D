/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:46:28 by pamone            #+#    #+#             */
/*   Updated: 2023/08/18 19:46:28 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
#include "/home/pamone/Desktop/mlx/libft/libft.h"

# ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000

# endif

// char	*get_next_line(int fd);
// char	*ft_remain_str(char *remain_str);
// char	*ft_get_line(char *remain_str);
// char	*ft_strjoin(char *remain_str, char *buff);
// char	*ft_strchr(char *s, int c);
// char	*ft_read_remain_str(int fd, char *remain_str);

char	*get_next_line(int fd);
char	*ft_read_to_left_str(int fd, char *left_str);
char	*ft_strchr_get(char *s, int c);
char	*ft_strjoin_get(char *left_str, char *buff);
size_t	ft_strlen_get(char *s);
char	*ft_get_line(char *left_str);
char	*ft_new_left_str(char *left_str);

#endif