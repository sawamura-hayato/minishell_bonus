/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:44:24 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 15:28:09 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "library.h"

char	*try_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char *)try_calloc((ft_strlen(s1) + 1), sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
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
//     char* target2 = try_strdup(source);
//     printf("origin target%p(%s)\n", target, target);
//     printf("origin source%p(%s)\n", source, source);
//     printf("my     target2%p(%s)\n", target2, target2);
//     printf("my     source2%p(%s)\n",source2, source2);
//     return 0;
// }
