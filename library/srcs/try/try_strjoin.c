/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:31:28 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/08 15:44:59 by tatyu            ###   ########.fr       */
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

char	*try_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	
	new_str = try_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	ft_memcpy((void *)new_str, (void *)s1, ft_strlen(s1));
	ft_memcpy((void *)&new_str[ft_strlen(s1)], (void *)s2, ft_strlen(s2));
	return (new_str);
}
