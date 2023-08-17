/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:38:47 by tterao            #+#    #+#             */
/*   Updated: 2023/08/17 17:49:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	cd_exec(char *path, t_data *d);

#include <stdio.h>
bool	cd_is_cdpath(char *path)
{
	const char	*curdir = "./";
	const char	*prevdir = "../";

	return (
		*path != '/'
		&& ft_strncmp(path, curdir, ft_strlen(curdir)) != 0
		&& ft_strncmp(path, prevdir, ft_strlen(prevdir)) != 0
	);
}

static char	*cdpath_doublecolon(char *cdpath)
{
	char	*new_cdpath;
	char	*target;

	target = ft_strstr(cdpath, "::");
	if (target == NULL)
		return (cdpath);
	new_cdpath = try_substr(cdpath, 0, target - &cdpath[0]);
	new_cdpath = try_strjoin_free(new_cdpath, ".:");
	new_cdpath = try_strjoin_free(new_cdpath, (target + 2));
	free(cdpath);
	return (cdpath_doublecolon(new_cdpath));
}

static char	*cdpath_singlecolon(char *cdpath)
{
	char	*new_cdpath;
	char	*target;

	if (*cdpath == '\0')
	{
		free(cdpath);
		return (".:");
	}
	target = ft_memchr(cdpath, ':', ft_strlen(cdpath));
	if (target == NULL)
		return (cdpath);
	printf("target %s\n", target);
	while (target != NULL)
	{
		if (*(target + 1) == '\0')
			break ;
		target = ft_memchr(target + 1, ':', ft_strlen(target + 1));
	}
	if (target == NULL || *(target + 1) != '\0')
		return (cdpath);
	new_cdpath = try_substr(cdpath, 0, target - &cdpath[0]);
	new_cdpath = try_strjoin_free(new_cdpath, ".:");
	free(cdpath);
	return (cdpath);
}

void	cd_cdpath(char *path, t_data *d)
{
	char	*cdpath;

	cdpath = envs_get_value("CDPATH", d->envs_hashmap);
	printf("%s\n", cdpath);
	if (cdpath == NULL)
		return (cd_exec(path, d));
	cdpath = cdpath_doublecolon(cdpath);
	printf("%s\n", cdpath);
	cdpath = cdpath_singlecolon(cdpath);
	printf("%s\n", cdpath);

}
