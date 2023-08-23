/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:21:48 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/22 20:16:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool	try_chdir(const char *og_path, const char *path, t_data *d)
{
	char	*msg;

	if (chdir(path) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		msg = try_strjoin("cd: ", og_path);
		perror(msg);
		free(msg);
		return (false);
	}
	return (true);
}
