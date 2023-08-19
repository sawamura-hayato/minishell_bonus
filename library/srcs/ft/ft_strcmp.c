/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:57:56 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 10:59:20 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str);

static size_t	get_len(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*casted_s1;
	const unsigned char	*casted_s2;
	size_t				i;
	size_t				len;
	int					diff;

	casted_s1 = (const unsigned char *)s1;
	casted_s2 = (const unsigned char *)s2;
	len = get_len(s1, s2);
	i = 0;
	while (i < len)
	{
		diff = casted_s1[i] - casted_s2[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
