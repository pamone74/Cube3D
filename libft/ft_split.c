/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:58:59 by pamone            #+#    #+#             */
/*   Updated: 2023/07/27 19:32:24 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * the ft_strclen get the len of the string before the delimeter.
 * For exmple when we pass "42 Abu dhabi" as a string, it will return
 *  len of 2 for 42 if the seperator is " "
 * 
*/
static size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	free_split(char **split)
{
	char	**ptr;

	if (split == NULL)
		return ;
	ptr = split;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free (split);
}
/**
 * is_string is a flag used to see if the pointer of
 * the string is being counted or not.
 * 0 is false and 1 is true
 * if (*s != c && !is_substring) :-> if the pointer 
 * of string is not the seperator, and 
 * there is no active substring being counted,then 
 * we have got our new string.
 * then is_substring will be 1 which true meaning t
 * hat we have got our first sub string
 * and we increment count. After that, the next 
 * condition will be false because *s!=c
 * so s++ to the next character, both of the if 
 * conditions will be false because is_string 
 * is false and s!=c is true but it won't satisfy 
 * the if (*s != c && !is_substring).
 * Then it will iterates untill it find the seperator 
 * then it will reset the is_string to true 1.
 * for example "42 Abu Dhabi" will return 3,
 * because there are three substrings.
*/

static size_t	count_substrings(const char *s, char c)
{
	size_t	count;
	int		is_substring;

	count = 0;
	is_substring = 0;
	while (*s)
	{
		if (*s != c && !is_substring)
		{
			is_substring = 1;
			count++;
		}
		else if (*s == c && is_substring)
			is_substring = 0;
		s++;
	}
	return (count);
}
/**
 * the split returns pointers of the substrings
 * seperated by the delimeter
 * **split is the memory allocated to return the 
 * pointer. so count_subsrings = 3 for "42 abu dhabi"
 * substrings = count_substrings(s, c); will be 3;
 * split = malloc((substrings + 1) * sizeof(char *));
 * will allocate memory for 3 subtrings +1 for NULL pointer
 * while (i < substrings) will run untill i is equal to 3
 * for example if we pass "42 abu dhabi", in the first
 * iteration, i = 0; and will skip the inner while function because
 * it is false so split[0] = ft_substr("42 Abu dhabi", 0,2),
 * 2 is the ft_strclen("42 abu dhabi", 32) so the substing will return 42
 * and the pointer of split[0] will return 42, 
 * s += ft_strclen() will be 0 + 2 which will be 2 and i++ will be 1,
 * and while(*s == c) will be true so s++ will be incremented so 2 + 1 = 3
 * son split[1] and the ft_substr(will point at s position 3, 0, 3) the
 * ft_strlen(s, c) will be 3 because the index of s is 3 pointing to A in (Abu)
 * so split[1] = abu, then i++ = 3, s = s + 3 , = 3 +3 = 6; then s++ 6+1 = 7
 * then the split[2] = dhabi then while loop will be false 
*/

char	**ft_split(char const *s, char c)
{
	size_t	substrings;
	char	**split;
	size_t	i;

	substrings = count_substrings(s, c);
	split = malloc((substrings + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i < substrings)
	{
		while (*s == c)
			s++;
		split[i] = ft_substr(s, 0, ft_strclen(s, c));
		if (!split[i])
		{
			free_split(split);
			return (NULL);
		}
		s += ft_strclen(s, c);
		i++;
	}
	split[i] = NULL;
	return (split);
}

// int main()
// {
// 	int i = 0;
// 	char **str = ft_split("42 Abu dhabi", ' ');
// 	while(str[i] != NULL)
// 	{	
// 		printf("The returned string value is %s\n", str[i]);
// 		i++;
// 	}
// }
