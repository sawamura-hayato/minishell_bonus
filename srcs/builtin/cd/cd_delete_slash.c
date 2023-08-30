/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_slash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:58:20 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 15:01:45 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "library.h"

char	*cd_replace_non_leading_consecutive_slashes(char *path);
char	*cd_delete_leading_slashes(char *path);

static size_t	get_trailing_slashes(char *path)
{
	size_t	i;

	i = ft_strlen(path) - 1;
	while (true)
	{
		if (i == 0)
			break ;
		if (path[i] != '/')
		{
			i++;
			break ;
		}
		i--;
	}
	return (i);
}

static char	*cd_delete_trailing_slash(char *path)
{
	char			*newpath;
	const size_t	trailing_slashes = get_trailing_slashes(path);

	if (trailing_slashes == 0)
		return (path);
	newpath = try_substr(path, 0, &path[trailing_slashes] - path);
	free(path);
	return (newpath);
}

char	*cd_delete_slash(char *path)
{
	path = cd_delete_trailing_slash(path);
	path = cd_replace_non_leading_consecutive_slashes(path);
	path = cd_delete_leading_slashes(path);
	return (path);
}
