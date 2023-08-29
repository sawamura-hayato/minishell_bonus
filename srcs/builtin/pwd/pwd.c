/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:05:20 by tterao            #+#    #+#             */
/*   Updated: 2023/08/29 20:38:37 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	put_error(t_data *d)
{
	const char	*msg = "pwd: error retrieving current directory:"
		" getcwd: cannot access parent directories: Permission denied\n";

	d->exit_status = EXIT_FAILURE;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

void	builtin_pwd(t_data *d)
{
	char	*cwd;

	d->exit_status = EXIT_SUCCESS;
	if (d->pwd == NULL)
		return (put_error(d));
	cwd = try_strjoin(d->pwd, "\n");
	try_write(STDOUT_FILENO, cwd, ft_strlen(cwd), d);
	free(cwd);
}
