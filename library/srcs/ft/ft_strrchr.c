/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:11:01 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/18 14:32:30 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

char	*ft_strrchr(const char *s, int c)
{
	char	converted_c;
	size_t	len;

	converted_c = (char)c;
	len = ft_strlen(s);
	while (true)
	{
		if (s[len] == converted_c)
			return ((char *)&s[len]);
		if (len == 0)
			break ;
		len--;
	}
	return (NULL);
}
