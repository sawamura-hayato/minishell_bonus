/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_leading_slashes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:46:45 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 15:04:56 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "library.h"
#define REPLACING_SLASH_NUM 3

char	*cd_delete_leading_slashes(char *path)
{
	char	*newpath;
	char	*first_slashes;

	if (*path != '/')
		return (path);
	first_slashes = path;
	while (*first_slashes != '\0')
	{
		if (*first_slashes != '/')
			break ;
		first_slashes++;
	}
	if ((first_slashes - path) < REPLACING_SLASH_NUM)
		return (path);
	newpath = try_strjoin("/", first_slashes);
	free(path);
	return (newpath);
}
