/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:37:30 by tterao            #+#    #+#             */
/*   Updated: 2023/08/17 18:42:18 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

bool	cd_iserror(char **argv)
{
	size_t	size;

	size = 0;
	while (argv[size] != NULL)
		size++;
	return (size > 2);
}

void	cd_put_error_too_many_args(t_data *d)
{
	const char	*msg = "cd: too many arguments\n";

	d->exit_status = EXIT_FAILURE;
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

void	cd_put_error_no_pwd(char *path, t_data *d)
{
	char	*msg;

	d->exit_status = EXIT_FAILURE;
	msg = try_strdup("cd: ");
	try_strjoin_free(msg, path);
	try_strjoin_free(msg, ": Permission denied\n");
	free(path);
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}
