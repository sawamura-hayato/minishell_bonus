/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:11 by tterao            #+#    #+#             */
/*   Updated: 2023/09/09 01:15:01 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include "init.h"
#include <stdlib.h>

bool	exit_is_overflow(char *str);
void	exit_put_error_numeric(t_data *d, char *str);
void	exit_put_error_too_many_args(t_data *d);
bool	exit_isspace(char c);

static bool	is_non_digit_arg(char *str)
{
	if (*str == '\0')
		return (true);
	while (exit_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (true);
		str++;
	}
	return (false);
}

static void	_exit_(bool is_parent_process, t_data *d)
{
	const char	*msg = "exit\n";

	if (is_parent_process)
		try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(d->exit_status);
}

void	builtin_exit(char **argv, bool is_parent_process, t_data *d)
{
	if (argv[1] == NULL)
		_exit_(is_parent_process, d);
	if (is_non_digit_arg(argv[1]))
		exit_put_error_numeric(d, argv[1]);
	if (exit_is_overflow(argv[1]))
		exit_put_error_numeric(d, argv[1]);
	if (argv[2] != NULL)
		return (exit_put_error_too_many_args(d));
	d->exit_status = (int)(unsigned char)ft_atol(argv[1]);
	_exit_(is_parent_process, d);
}
