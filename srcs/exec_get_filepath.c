/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_filepath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:22:27 by tterao            #+#    #+#             */
/*   Updated: 2023/08/23 17:44:55 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_execution.h"
#include <stdlib.h>
#define COLON ":"

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

bool	exec_is_commnad_with_permission(char *filepath)
{
	struct stat	sb;

	if (stat(filepath, &sb) == -1)
		return (false);
	if (!S_ISDIR(sb.st_mode) && access(filepath, X_OK) == 0)
		return (true);
	return (false);
}

char	*exec_get_filepath(char *path, char *command, char *last_colon)
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
	if (exec_is_commnad_with_permission(eachpath))
	{
		free(path);
		return (eachpath);
	}
	if (colon != NULL)
		colon += ft_strlen(COLON);
	return (exec_get_filepath(path, command, colon));
}
