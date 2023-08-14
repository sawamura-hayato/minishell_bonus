/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:49:11 by tterao            #+#    #+#             */
/*   Updated: 2023/08/14 18:56:56 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include "init.h"
#include <stdlib.h>

void	overflow(char *str, t_data *d);

enum
{
	EXIT_NUMERIC_ARG = 2,
};

static void	is_args_digit(char *str, t_data *d)
{
	char	*msg;

	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
		{
			msg = try_strdup("exit\nexit: ");
			msg = try_strjoin_free(msg, str);
			msg = try_strjoin_free(msg, ": numeric argument required\n");
			try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
			free(msg);
			exit(EXIT_NUMERIC_ARG);
		}
		str++;
	}
}


void	builtin_exit(char **argv, t_data *d)
{
	if (argv[1] == NULL)
		exit(d->exit_status);
	is_args_digit(argv[1], d);
	ioverflow(argv[1], d);
}
