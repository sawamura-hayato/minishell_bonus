/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:57:56 by tterao            #+#    #+#             */
/*   Updated: 2023/08/05 17:05:21 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*casted_s1;
	const unsigned char	*casted_s2;
	size_t				i;
	size_t				len;
	int					diff;

	casted_s1 = (const unsigned char *)s1;
	casted_s2 = (const unsigned char *)s2;
	len = ft_strlen(s1);
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
