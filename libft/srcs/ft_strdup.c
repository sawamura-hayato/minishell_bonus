/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:44:24 by hsawamur          #+#    #+#             */
/*   Updated: 2023/01/21 13:39:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// #include <string.h>
// #include <stdio.h>

// int main()
// {
//     char source[] = "GeeksForGeeks";
//     char source2[] = "GeeksForGeeks";
//     // A copy of source is created dynamically
//     // and pointer to copy is returned.
//     char* target = strdup(source);
//     char* target2 = ft_strdup(source);
//     printf("origin target%p(%s)\n", target, target);
//     printf("origin source%p(%s)\n", source, source);
//     printf("my     target2%p(%s)\n", target2, target2);
//     printf("my     source2%p(%s)\n",source2, source2);
//     return 0;
// }
