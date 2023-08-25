/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_convert_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:32 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/25 18:45:03 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	cd_put_error_no_pwd(char *path, t_data *d);
char	*cd_delete_dot_slash(char *path, char *last_ds);
char	*cd_delete_dotdot(char *path, char *last_ddc);
void	cd_put_error_file(const char *og_path, t_data *d);
char	*cd_delete_dotdot_if_needed(char *path, char *last_ddc);
char	*cd_delete_slash(char *path);
void	cd_exec(const char *og_path, char *path, bool is_cdpath, t_data *d);

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
	printf("%s\n", path);
	if (path == NULL)
		return ;
	if (*path != '/')
		path = cd_join_pwd(path, d);
	if (path == NULL)
		return ;
	printf("%s\n", path);
	path = cd_delete_dot_slash(path, path);
	printf("dotdot削除前\n");
	printf("%s\n", path);
	path = cd_delete_dotdot(path, path);
	if (path == NULL)
		return (cd_put_error_file(og_path, d));
	printf("dotdot削除後\n");
	printf("%s\n", path);
	path = cd_delete_dotdot_if_needed(path, path);
	// printf("%s\n", path);
	path = cd_delete_slash(path);

	printf("%s\n\n", path);
	printf("----------------------------------------------\n");
	// cd_exec(og_path, path, is_cdpath, d);
	(void)is_cdpath;
}
