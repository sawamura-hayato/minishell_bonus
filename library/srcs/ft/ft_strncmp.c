/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:32:14 by tterao            #+#    #+#             */
/*   Updated: 2023/08/16 19:33:16 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;
	int				diff;
	size_t			i;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	diff = 0;
	i = 0;
	while (i < n)
	{
		diff = *casted_s1 - *casted_s2;
		if (!*casted_s1 || !*casted_s2)
			break ;
		if (diff != 0)
			return (diff);
		casted_s1++;
		casted_s2++;
		i++;
	}
	return (diff);
}
