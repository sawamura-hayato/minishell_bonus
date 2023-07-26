/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:52:52 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/26 16:19:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_substred(const char *s, unsigned int start, size_t end)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t end)
{
	size_t	s_len;
	// size_t	diff_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t) start >= s_len || end == 0)
		return (ft_strdup(""));
	// diff_len = s_len - start;
	// if (diff_len <= end)
	// 	return (ft_substred(s, start, diff_len));
	return (ft_substred(s, start, end));
}

// #include "stdio.h"
// int main(void)
// {
// 	char str[] = "abcdef";
// 	char s[] = "libft-tokyo-tester";
// 	printf("ft_substr()   %s\n", ft_substr(s, 10, 100));
// 	printf("s   %s\n", s + 10);
// 	printf("ft_substr()   %s\n", ft_substr(s, 10, 5));
// 	printf("ft_substr()   %s\n", ft_substr(s, 15, 5));
// 	printf("ft_substr()   %s\n", ft_substr(str, 5, 0));
// 	printf("ft_substr()   %s\n", ft_substr(str, 5, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 6, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 0, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 2, 10));
// 	printf("ft_substr()   %s\n", ft_substr(str, 0, 100));
// 	return (0);
// }