/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_convert_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:32 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/20 18:01:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#define DS "./"

void	cd_put_error_no_pwd(char *path, t_data *d);

#include <stdio.h>
static char	*cd_join_pwd(char *path, t_data *d)
{
	char	*newpath;

	if (d->pwd == NULL)
	{
		cd_put_error_no_pwd(path, d);
		return (NULL);
	}
	if (d->pwd[ft_strlen(d->pwd) - 1] == '/')
		newpath = try_strdup(d->pwd);
	else
		newpath = try_strjoin(d->pwd, "/");
	newpath = try_strjoin_free(newpath, path);
	free(path);
	return (newpath);
}

static char	*cd_delete_dot_slash(char *path)
{
	char	*newpath;
	char	*dot_slash;

	dot_slash = ft_strstr(path, "./");
	if (dot_slash == NULL)
		return (path);
	newpath = try_substr(path, 0, dot_slash - path);
	newpath = try_strjoin_free(newpath, try_strdup(dot_slash + ft_strlen(DS)));
	free(path);
	return (cd_delete_dot_slash(newpath));
}

void	cd_convert_path_and_exec(char *path, t_data *d, bool is_cdpath)
{
	printf("%s %d\n", path, is_cdpath);
	if (path == NULL)
		return ;
	if (*path != '/')
		path = cd_join_pwd(path, d);
	if (path == NULL)
		return ;
	path = cd_delete_dot_slash(path);
	printf("%s\n", path);
}
