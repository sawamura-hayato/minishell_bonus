/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_put_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:08:12 by tterao            #+#    #+#             */
/*   Updated: 2023/09/15 16:27:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "exec_command.h"
#include <stdlib.h>

bool	is_path(const char *command);
char	*exec_convert_filepath(t_data *d);
char	*exec_get_filepath_for_error(char *path, char *command,
			char *last_colon);

void	exec_put_error_is_dir(const char *command, t_data *d)
{
	char	*msg;

	msg = try_strjoin(command, ": Is a directory\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	exec_put_error_no_file(const char *command, t_data *d)
{
	char	*msg;

	msg = try_strjoin(command, ": No such file or directory\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	exit(COMMAND_NOT_FOUND);
}

void	exec_put_error_no_permission(char *command, t_data *d)
{
	char	*path;
	char	*tmp;

	path = exec_convert_filepath(d);
	if (!is_path(command) && envs_get_node("PATH", d->envs_hashmap) != NULL)
	{
		tmp = command;
		command = exec_get_filepath_for_error(path, command, path);
		free(tmp);
	}
	free(path);
	command = try_strjoin_free(command, ": Permission denied\n");
	try_write(STDERR_FILENO, command, ft_strlen(command), d);
	free(command);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	exec_put_error_cmd_not_found(const char *command, t_data *d)
{
	char	*msg;

	msg = try_strjoin(command, ": command not found\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	exit(COMMAND_NOT_FOUND);
}

void	exec_put_error_ambiguous_redirect(char *file, t_data *d)
{
	char	*msg;

	d->exit_status = EXIT_FAILURE;
	msg = try_strjoin(file, ": ambiguous redirect\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}
