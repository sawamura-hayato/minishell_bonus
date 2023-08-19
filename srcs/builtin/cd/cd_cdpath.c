/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:38:47 by tterao            #+#    #+#             */
/*   Updated: 2023/08/19 19:04:16 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define CUR_DIR "./"
#define PRE_DIR "../"
#define DOT "."
#define DOTDOT ".."

void	cd_exec(char *path, t_data *d);
void	cd_convert_path(char *path, t_data *d, bool is_cdpath);
void	cd_put_error_no_pwd(char *path, t_data *d);

#include <stdio.h>
bool	cd_is_cdpath(char *path)
{
	char	*dot_ptr;

	if (*path == '/')
		return (false);
	dot_ptr = ft_strstr(path, PRE_DIR);
	if (dot_ptr == path)
		return (false);
	dot_ptr = ft_strstr(path, CUR_DIR);
	if (dot_ptr == path)
		return (false);
	dot_ptr = ft_strstr(path, DOTDOT);
	if (dot_ptr == path && *(dot_ptr + ft_strlen(DOTDOT)) == '\0')
		return (false);
	dot_ptr = ft_strstr(path, DOT);
	if (dot_ptr == path && *(dot_ptr + ft_strlen(DOT)) == '\0')
		return (false);
	return (true);
}

char	*cd_join_pwd(char *path, t_data *d)
{
	char	*new_path;

	if (d->pwd == NULL)
	{
		cd_put_error_no_pwd(path, d);
		return (NULL);
	}
	new_path = try_strjoin(d->pwd, "/");
	new_path = try_strjoin_free(new_path, path);
	free(path);
	return (new_path);
}

static char	*join_path(char *eachpath, char *path)
{
	if (*(eachpath + ft_strlen(eachpath) - 1) != '/')
		eachpath = try_strjoin_free(eachpath, "/");
	eachpath = try_strjoin_free(eachpath, path);
	return (eachpath);
}

bool	is_dir_with_permission(char *dirpath, t_data *d)
{
	struct stat	*sb;

	if (stat(dirpath, sb) == -1)
		return (false);
	if (S_ISDIR(sb->st_mode) && access(dirpath, X_OK) == 0)
		return (true);
	return (false);
}

static	char	*dup_dot(char *colon, bool *is_cdpath)
{
	(void *)colon;
	*is_cdpath = false;
	return (try_strdup("."));
}

static void	cd_cdpath_loop(char *path, char *cdpath, t_data *d)
{
	char	*colon;
	char	*eachpath;
	bool	is_cdpath;

	is_cdpath = true;
	if (cdpath == NULL || *cdpath == '\0')
		return (cd_convert_path(join_path(try_strdup("."), path), d, false));
	colon = ft_memchr((void *)cdpath, ':', ft_strlen(cdpath));
	if (colon != NULL && (cdpath == colon && *(cdpath + 1) == ':'))
		eachpath = dup_dot(colon++, &is_cdpath);
	else if (*cdpath == ':' || *(cdpath + 1) == '\0')
		eachpath = dup_dot(colon, &is_cdpath);
	else if (colon != NULL)
		eachpath = try_substr(cdpath, 0, (colon - cdpath));
	else
		eachpath = try_strdup(cdpath);
	if (colon != NULL)
		colon++;
	eachpath = join_path(eachpath, path);
	if (is_dir_with_permission(eachpath, d))
		return (cd_convert_path(eachpath, d, is_cdpath));
	free(eachpath);
	return (cd_cdpath_loop(path, colon, d));
}


void	cd_cdpath(char *path, t_data *d)
{
	char	*cdpath;

	cdpath = envs_get_value("CDPATH", d->envs_hashmap);
	printf("%s\n", cdpath);
	if (cdpath == NULL || *cdpath == '\0')
	{
		free(cdpath);
		return (cd_convert_path(join_path(try_strdup("."), path), d, false));
	}
	cd_cdpath_loop(path, cdpath, d);

}
