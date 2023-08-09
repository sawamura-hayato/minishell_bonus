/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ignorecase.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:43:53 by ttesrao            #+#    #+#             */
/*   Updated: 2023/08/09 18:51:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

char	ft_tolower(char c)
{
	if (ft_isupper(c))
		return (c - ('a' - 'A'));
	else
		return (c);
}

int	ft_strcmp_ignorecase(const char *s1, const char *s2)
{
	const unsigned char	*casted_s1;
	const unsigned char	*casted_s2;

	casted_s1 = (const unsigned char *)s1;
	casted_s2 = (const unsigned char *)s2;
	while (ft_tolower(*casted_s1) == ft_tolower(*casted_s2))
	{
		if (*casted_s1 == '\0')
			break ;
		casted_s1++;
		casted_s2++;
	}
	return (ft_tolower(*casted_s1) - ft_tolower(*casted_s2));
}
