/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:06:08 by tterao            #+#    #+#             */
/*   Updated: 2023/08/14 15:50:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

static bool	is_noption(char *str)
{
	return (str[0] == '-' && str[1] == 'n');
}

static char	**echo_option(char **argv)
{
	size_t	i;

	while (*argv != NULL)
	{
		if (is_noption(*argv) == false)
			break ;
		i = 1;
		while (*argv[i] != '\0')
		{
			if (*argv[i] != 'n')
				break ;
			i++;
		}
		argv++;
	}
	return (argv);
}

static char	*make_str(char **argv)
{
	char	*str;

	str = try_strdup("");
	if (argv == NULL)
		return (str);
	while (true)
	{
		str = try_strjoin_free(str, *argv);
		argv++;
		if (*argv == NULL)
			break ;
		str = try_strjoin_free(str, " ");
	}
	return (str);
}

static void	put_str(char *str, bool n_option, t_data *d)
{
	if (n_option == false)
		str = try_strjoin_free(str, "\n");
	try_write(STDOUT_FILENO, str, ft_strlen(str), d);
	free(str);
}

void	builtin_echo(char **argv, t_data *d)
{
	bool	n_option;
	char	**args;
	char	*str;

	d->exit_status = EXIT_SUCCESS;
	if (argv[1] == NULL)
		return (put_str(try_strdup(""), false, d));
	args = echo_option(&argv[1]);
	if (argv != args)
		n_option = true;
	else
		n_option = false;
	str = make_str(args);
	put_str(str, n_option, d);
}
