/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:26:00 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 15:43:16 by tterao           ###   ########.fr       */
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

void	exit_put_error_numeric(t_data *d, char *str)
{
	char	*msg;

	d->exit_status = EXIT_NUMERIC_ARG;
	msg = try_strdup("exit\nexit: ");
	msg = try_strjoin_free(msg, str);
	msg = try_strjoin_free(msg, ": numeric argument required\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	exit(d->exit_status);
}

void	exit_put_error_too_many_args(t_data *d)
{
	const char	*msg = "exit\nexit: too many arguments\n";

	d->exit_status = TOO_MANY_ARGS;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}
