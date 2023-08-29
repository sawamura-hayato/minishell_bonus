/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:50:55 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/26 15:57:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*new_b;
	size_t			i;

	new_b = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		new_b[i] = c;
		i++;
	}
	return (new_b);
}
