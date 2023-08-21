/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_convert_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:32 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/21 18:13:18 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	cd_put_error_no_pwd(char *path, t_data *d);
char	*cd_delete_dot_slash(char *path, char *last_ds);
char	*cd_delete_dotdot(char *path, char *last_ddc);
void	cd_put_error_file(const char *og_path, t_data *d);

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

#include <stdio.h>
void	cd_convert_path_and_exec(const char *og_path, char *path,
									t_data *d, bool is_cdpath)
{
	printf("%s %d\n", path, is_cdpath);
	if (path == NULL)
		return ;
	if (*path != '/')
		path = cd_join_pwd(path, d);
	if (path == NULL)
		return ;
	path = cd_delete_dot_slash(path, path);
	printf("%s\n", path);
	path = cd_delete_dotdot(path, path);
	if (path == NULL)
		return (cd_put_error_file(og_path, d));
	printf("%s\n", path);
}
