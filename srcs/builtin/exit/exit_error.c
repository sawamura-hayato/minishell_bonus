/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:26:00 by tterao            #+#    #+#             */
/*   Updated: 2023/09/20 18:31:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include "init.h"
#include <stdlib.h>

enum
{
	TOO_MANY_ARGS = 1,
	EXIT_NUMERIC_ARG = 2,
};

void	exit_put_error_numeric(t_data *d, bool is_parent_process, char *str)
{
	char	*msg;
	char	*tmp;

	d->exit_status = EXIT_NUMERIC_ARG;
	msg = try_strjoin("exit: ", str);
	msg = try_strjoin_free(msg, ": numeric argument required\n");
	if (is_parent_process)
	{
		tmp = msg;
		msg = try_strjoin("exit\n", msg);
		free(tmp);
	}
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	exit(d->exit_status);
}

void	exit_put_error_too_many_args(bool is_parent_process, t_data *d)
{
	char	*msg;
	char	*tmp;

	msg = try_strdup("exit: too many arguments\n");
	if (is_parent_process)
	{
		tmp = msg;
		msg = try_strjoin("exit\n", msg);
		free(tmp);
	}
	d->exit_status = TOO_MANY_ARGS;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}
