/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_make_filepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:17:42 by tterao            #+#    #+#             */
/*   Updated: 2023/09/15 15:11:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "library.h"
#include <stdlib.h>
#define COLON ":"
#define D_COLON "::"
#define DOT_COMP "./"
#define DOTDOT_COMP "../"

char	*exec_get_filepath(char *path, char *command,
			bool *filepath_exist, char *last_colon);
bool	exec_is_commnad_with_permission(char *filepath, bool *filepath_exist);

static char	*add_currentpath_double_colon(char *path)
{
	char	*newpath;
	char	*double_colon;

	double_colon = ft_strstr(path, D_COLON);
	if (double_colon == NULL)
		return (path);
	if (path == double_colon)
		newpath = try_strjoin("./", path + ft_strlen(COLON));
	else
	{
		newpath = try_substr(path, 0, double_colon - path);
		newpath = try_strjoin_free(newpath, ":./:");
		newpath = try_strjoin_free(newpath, double_colon + ft_strlen(D_COLON));
	}
	free(path);
	return (add_currentpath_double_colon(newpath));
}

static char	*add_currentpath_single_colon(char *path)
{
	if (*path == ':')
		path = try_strjoin("./", path);
	if (path[ft_strlen(path) - 1] == ':')
		path = try_strjoin_free(path, "./");
	return (path);
}

static bool	is_absolute_path_with_permission(t_ast *node, bool *filepath_exist)
{
	const char	*cmd = node->command_list->word_list->word;

	if (*cmd != '/' && ft_strncmp(cmd, DOT_COMP, ft_strlen(DOT_COMP)) != 0
		&& ft_strncmp(cmd, DOTDOT_COMP, ft_strlen(DOTDOT_COMP)) != 0)
		return (false);
	return (
		exec_is_commnad_with_permission(node->command_list->word_list->word,
			filepath_exist)
	);
}

char	*exec_make_filepath(t_ast *node, bool *filepath_exist, t_data *d)
{
	char	*path;

	if (node->command_list->word_list == NULL
		|| node->command_list->word_list->word == NULL)
		return (NULL);
	if (is_absolute_path_with_permission(node, filepath_exist))
		return (try_strdup(node->command_list->word_list->word));
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
	path = exec_get_filepath(path, node->command_list->word_list->word,
			filepath_exist, path);
	return (path);
}
