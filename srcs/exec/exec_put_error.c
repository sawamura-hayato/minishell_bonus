/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_put_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 22:08:12 by tterao            #+#    #+#             */
/*   Updated: 2023/08/25 11:14:25 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "exec_command.h"
#include <stdlib.h>

void	exec_put_error_is_dir(const char *command, t_data *d)
{
	const char	*msg = try_strjoin(command, ": Is a directory\n");

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	exec_put_error_no_file(const char *command, t_data *d)
{
	const char	*msg = try_strjoin(command, ": No such file or directory\n");

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	exec_put_error_no_permission(const char *command, t_data *d)
{
	const char	*msg = try_strjoin(command, ": Permission denied\n");

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	exec_put_error_cmd_not_found(const char *command, t_data *d)
{
	const char	*msg = try_strjoin(command, ": command not found\n");

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(COMMAND_NOT_FOUND);
}

