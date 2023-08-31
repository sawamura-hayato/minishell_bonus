/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:38:47 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 20:07:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void	cd_exec(const char *og_path, char *path, bool is_cdpath, t_data *d);
void	cd_convert_path_and_exec(const char *og_path, char *path,
			t_data *d, bool is_cdpath);
void	cd_put_error_no_pwd(char *path, t_data *d);
char	*cd_newcdpath(char *cdpath, char *colon);

static char	*join_path(char *eachpath, char *path)
{
	if (*(eachpath + ft_strlen(eachpath) - 1) != '/')
		eachpath = try_strjoin_free(eachpath, "/");
	eachpath = try_strjoin_free(eachpath, path);
	return (eachpath);
}

bool	cd_is_dir_with_permission(char *path, char *dirpath)
{
	struct stat	sb;
	bool		has_permission;

	has_permission = false;
	if (stat(dirpath, &sb) == -1)
	{
		free(dirpath);
		return (false);
	}
	if (S_ISDIR(sb.st_mode) && access(dirpath, X_OK) == 0)
		has_permission = true;
	if (S_ISLNK(sb.st_mode) && access(dirpath, X_OK) == 0)
		has_permission = true;
	if (has_permission)
		free(path);
	else
		free(dirpath);
	return (has_permission);
}

static	char	*dup_dot(char *colon, bool *is_cdpath)
{
	(void)colon;
	*is_cdpath = false;
	return (try_strdup("."));
}

static void	cd_cdpath_loop(const char *og_path, char *path,
							char *cdpath, t_data *d)
{
	char	*colon;
	char	*eachpath;
	bool	is_cdpath;

	is_cdpath = true;
	if (cdpath == NULL || *cdpath == '\0')
		return (cd_convert_path_and_exec(og_path, path, d, false));
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
	if (cd_is_dir_with_permission(path, eachpath))
		return (cd_convert_path_and_exec(og_path, eachpath, d, is_cdpath));
	return (cd_cdpath_loop(og_path, path, colon, d));
}

void	cd_cdpath(const char *og_path, char *path, t_data *d)
{
	char	*cdpath;

	cdpath = envs_get_value("CDPATH", d->envs_hashmap);
	if (cdpath == NULL || *cdpath == '\0')
	{
		free(cdpath);
		return (cd_convert_path_and_exec(og_path, path, d, false));
	}
	cd_cdpath_loop(og_path, path, cdpath, d);
	free(cdpath);
}
