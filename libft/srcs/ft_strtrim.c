/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:27:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/01/21 13:38:39 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char_in_str(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_trimed_str(char const*s1, size_t len)
{
	char		*res;
	size_t		i;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;
	size_t	end;

	if (s1 == NULL || s1[0] == '\0')
		return (ft_strdup(""));
	if (set == NULL)
		return (ft_strdup(s1));
	while (is_char_in_str(set, *s1))
		s1++;
	len_s1 = ft_strlen(s1);
	end = 0;
	if (len_s1 == end)
		return (ft_strdup(""));
	while (is_char_in_str(set, s1[len_s1 - end - 1]))
		end++;
	return (ft_trimed_str(s1, len_s1 - end));
}

// int main(void)
// {
// 	const char *str = "21211221212";
// 	const char *str2 = "21";
// 	char *s1 = "  \t \t \n   \n\n\n\t";
// 	char *s2 = "";
// 	char *ret = ft_strtrim(s1, " \n\t");

// 	// if (!strcmp(ret, s2))
// 	// 	printf("good");
// 	// printf("bad");
// 	printf("ft_strtrim()   %s\n", ret);
// 	printf("ft_strtrim()   %s\n", s2);
// 	printf("ft_strtrim()   %s\n", ft_strtrim(s1, " \n\t"));
// 	// printf("ft_is_strtrim()   %d\n",is_char_in_str(str, str2[0]));
// 	printf("ft_strtrim()   %s\n",ft_strtrim(str, str2));
// 	// printf("ft_strtrim()   %d\n",strcmp("", NULL));
// 	// printf("ft_strtrim()   %d\n",strcmp("", ""));
// 	// printf("ft_strtrim()   %s\n",ft_strtrim("", str2));
// 	// printf("ft_strtrim()   %s\n",ft_strtrim(str, ""));
// 	return (0);
// }