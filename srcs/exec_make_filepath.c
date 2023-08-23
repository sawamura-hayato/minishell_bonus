/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_make_filepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:17:42 by tterao            #+#    #+#             */
/*   Updated: 2023/08/23 15:55:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_execution.h"
#include "library.h"
#include <stdlib.h>
#define COLON ":"
#define D_COLON "::"

static char	*add_currentpath_double_colon(char *path)
{
	char	*newpath;
	char	*double_colon;

	double_colon = ft_strstr(path, D_COLON);
	newpath = try_substr(path, 0, double_colon - path);
	newpath = try_strjoin_free(newpath, ":.:");
	newpath = try_strjoin_free(newpath, path + ft_strlen(D_COLON));
	free(path);
	return (add_currentpath_double_colon(newpath));
}

static char	*add_currentpath_single_colon(char *path)
{
	if (*path == ':')
		path = try_strjoin_free("./", path);
	if (path[ft_strlen(path) - 1] == ':')
		path = try_strjoin_free(path, "./");
	return (path);
}

static char	*join_path_command(char *path, char *command, char *last_colon)
{
	char	*newpath;

	if (path[ft_strlen(path) - 1] != '/')
	{
		newpath = try_strjoin(last_colon, "/");
		newpath = try_strjoin_free(newpath, command);
	}
	else
		newpath = try_strjoin(last_colon, command);
	return (newpath);
}

bool	exec_is_commnad_with_permission(char *filepath)
{
	struct stat	sb;

	if (stat(filepath, &sb) == -1)
		return (false);
	if (!S_ISDIR(sb.st_mode) && access(filepath, X_OK) == 0)
		return (true);
	return (false);
}

static char	*get_filepath(char *path, char *command, char *last_colon)
{
	char	*eachpath;
	char	*colon;

	if (last_colon == '\0')
		return (NULL);
	colon = ft_strstr(last_colon, COLON);
	if (colon == NULL)
		eachpath = join_path_command(path, command, last_colon);
	else
		eachpath = try_substr(last_colon, 0, colon - last_colon);
	if (exec_is_commnad_with_permission(eachpath))
	{
		free(path);
		return (eachpath);
	}
	return (get_filepath(path, command, last_colon + ft_strlen(last_colon)));
}

char	*exec_make_filepath(t_ast *node, t_data *d)
{
	char	*path;

	path = envs_get_value("PATH", d->envs_hashmap);
	if (path == NULL || *path == '\0')
	{
		free(path);
		path = try_strdup("./");
	}
	else if (path != NULL)
	{
		path = add_currentpath_double_colon(path);
		path = add_currentpath_single_colon(path);
	}
	path = get_filepath(path, node->command_list->word_list->word);
}
