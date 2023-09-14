/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:20:02 by tterao            #+#    #+#             */
/*   Updated: 2023/09/14 12:54:03 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>

char	*try_substr(char const *s, size_t start, size_t len)
{
	char		*new_str;
	size_t		i;
	size_t		len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (try_strdup(""));
	if (len > len_s)
		len = len_s;
	new_str = try_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}
