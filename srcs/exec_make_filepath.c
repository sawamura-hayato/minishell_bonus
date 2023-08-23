/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_make_filepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:17:42 by tterao            #+#    #+#             */
/*   Updated: 2023/08/23 15:28:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_execution.h"
#include "init.h"
#include "parse.h"
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

static char	*join_path_command(char *path, char *command)
{
	if (path[ft_strlen(path) - 1] != '/')
		path = try_strjoin_free(path, "/");
	
}

static char	*get_filepath(char *path, char *command)
{
	char	*eachpath;
	char	*colon;

	colon = ft_strstr(path, COLON);
	if (colon == NULL)
		eachpath = join_path_command(path, command);
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
	get_filepath(path, node->command_list->word_list->word);
}
