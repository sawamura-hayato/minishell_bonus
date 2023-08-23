/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dot_slash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:06:51 by tterao            #+#    #+#             */
/*   Updated: 2023/08/21 15:19:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DOT "."
#define DS "./"

static	char	*cd_delete_last_dot(char *path)
{
	char		*newpath;
	const char	*last_comp = ft_strrchr(path, '/');

	if (last_comp == NULL || ft_strcmp(last_comp, "/.") != 0)
		return (path);
	newpath = try_substr(path, 0, (ft_strlen(path) - 1));
	free(path);
	return (newpath);
}

char	*cd_delete_dot_slash(char *path, char *last_ds)
{
	char	*newpath;
	char	*dot_slash;

	dot_slash = ft_strstr(last_ds, DS);
	if (dot_slash == NULL)
		return (cd_delete_last_dot(path));
	if (dot_slash != path && *(dot_slash - 1) == '.')
		return (cd_delete_dot_slash(path, (dot_slash + ft_strlen(DS))));
	newpath = try_substr(path, 0, dot_slash - path);
	newpath = try_strjoin_free(newpath, (dot_slash + ft_strlen(DS)));
	free(path);
	return (cd_delete_dot_slash(newpath, newpath));
}
