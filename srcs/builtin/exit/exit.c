/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:11 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 16:39:22 by tterao           ###   ########.fr       */
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

static bool	is_args_digit(char *str)
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

void	builtin_exit(char **argv, t_data *d)
{
	const char	*msg = "exit\n";

	if (argv[1] == NULL)
	{
		try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
		exit(d->exit_status);
	}
	if (is_args_digit(argv[1]))
		exit_put_error_numeric(d, argv[1]);
	if (exit_is_overflow(argv[1]))
		exit_put_error_numeric(d, argv[1]);
	if (argv[2] != NULL)
		return (exit_put_error_too_many_args(d));
	d->exit_status = (int)(unsigned char)ft_atol(argv[1]);
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(d->exit_status);
}
