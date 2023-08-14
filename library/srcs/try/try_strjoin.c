/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:31:28 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/14 22:43:37 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*casted_dest;
	const unsigned char	*casted_src;
	size_t				i;

	casted_dest = (unsigned char *)dest;
	casted_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		casted_dest[i] = casted_src[i];
		i++;
	}
	return (dest);
}

static char	*try_check_null_strjoin(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (try_strdup(s2));
	else if (s2 == NULL)
		return (try_strdup(s1));
	return (NULL);
}

char	*try_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	
	if (s1 == NULL || s2 == NULL)
		return (try_check_null_strjoin(s1, s2));
	new_str = try_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	ft_memcpy((void *)new_str, (void *)s1, ft_strlen(s1));
	ft_memcpy((void *)&new_str[ft_strlen(s1)], (void *)s2, ft_strlen(s2));
	return (new_str);
}
