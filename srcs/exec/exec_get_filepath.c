/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_filepath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:22:27 by tterao            #+#    #+#             */
/*   Updated: 2023/09/15 15:55:37 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include <stdlib.h>
#define COLON ":"

bool	is_file(const char *path);

static char	*join_path_command(char *command, char *path)
{
	char	*newpath;

	if (path[ft_strlen(path) - 1] != '/')
	{
		newpath = try_strjoin(path, "/");
		newpath = try_strjoin_free(newpath, command);
	}
	else
		newpath = try_strjoin(path, command);
	free(path);
	return (newpath);
}

bool	exec_is_commnad_with_permission(char *filepath, bool *filepath_exist)
{
	struct stat	sb;

	if (stat(filepath, &sb) == -1)
		return (false);
	if (access(filepath, F_OK) == 0)
		*filepath_exist = true;
	if (!S_ISDIR(sb.st_mode) && access(filepath, X_OK) == 0)
		return (true);
	return (false);
}

char	*exec_get_filepath(char *path, char *command,
							bool *filepath_exist, char *last_colon)
{
	char	*eachpath;
	char	*colon;

	if (last_colon == NULL || *last_colon == '\0')
		return (NULL);
	colon = ft_strstr(last_colon, COLON);
	if (colon == NULL)
		eachpath = join_path_command(command, try_strdup(last_colon));
	else
		eachpath = join_path_command(command,
				try_substr(last_colon, 0, colon - last_colon));
	if (exec_is_commnad_with_permission(eachpath, filepath_exist))
	{
		free(path);
		return (eachpath);
	}
	if (colon != NULL)
		colon += ft_strlen(COLON);
	return (exec_get_filepath(path, command, filepath_exist, colon));
}

char	*exec_get_filepath_for_error(char *path, char *command,
			char *last_colon)
{
	char	*eachpath;
	char	*colon;

	if (last_colon == NULL || *last_colon == '\0')
		return (NULL);
	colon = ft_strstr(last_colon, COLON);
	if (colon == NULL)
		eachpath = join_path_command(command, try_strdup(last_colon));
	else
		eachpath = join_path_command(command,
				try_substr(last_colon, 0, colon - last_colon));
	if (is_file(eachpath))
		return (eachpath);
	if (colon != NULL)
		colon += ft_strlen(COLON);
	return (exec_get_filepath_for_error(path, command, colon));
}
